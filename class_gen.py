#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
class_gen_full_v3.py
Robuste : génère .hpp/.cpp à partir de blocs ```mermaid``` contenant classDiagram.
Usage:
    python class_gen_full_v3.py README.md [--debug]
"""
import os
import re
import sys
from collections import defaultdict

if len(sys.argv) < 2:
    print("Usage: python class_gen_full_v3.py README.md [--debug]")
    sys.exit(1)

INPUT = sys.argv[1]
DEBUG = ("--debug" in sys.argv)
OUT_DIR = "class"

if not os.path.exists(INPUT):
    print(f"Fichier introuvable: {INPUT}")
    sys.exit(1)

os.makedirs(OUT_DIR, exist_ok=True)
text = open(INPUT, "r", encoding="utf-8").read()

# 1) Extraire tous les blocs mermaid (tolère espace après ```mermaid)
mermaid_blocks = []
for m in re.finditer(r"```mermaid\s*(.*?)```", text, flags=re.DOTALL | re.IGNORECASE):
    mermaid_blocks.append(m.group(1))
if not mermaid_blocks:
    print("Aucun bloc ```mermaid``` trouvé.")
    sys.exit(1)
mermaid_all = "\n".join(mermaid_blocks)

# 2) Héritage (Child --|> Parent)
inheritances = []
for m in re.finditer(r"([A-Za-z_]\w*)\s*--\|>\s*([A-Za-z_]\w*)", mermaid_all):
    inheritances.append((m.group(1), m.group(2)))
parent_of = {}
children_of = defaultdict(list)
for c, p in inheritances:
    parent_of[c] = p
    children_of[p].append(c)

# 3) Récupérer classes : prend en charge 'class Name { ... }' sur plusieurs lignes
class_pattern = re.compile(r"class\s+([A-Za-z_]\w*)\s*{(.*?)}", flags=re.DOTALL)
classes = {}

for cm in class_pattern.finditer(mermaid_all):
    name = cm.group(1)
    body = cm.group(2).strip()
    # split lines, trim whitespace, ignore empty
    lines = [ln.strip() for ln in body.splitlines() if ln.strip() != ""]
    classes[name] = {"lines": lines, "attrs": [], "methods": []}

if DEBUG:
    print("Classes trouvées:", list(classes.keys()))
    print("Héritages:", inheritances)

# helpers pour conversion des types
def convert_type(typ: str):
    if typ is None:
        return "void"
    t = typ.strip()
    # detect array notation like [][] or []
    arr_levels = t.count("[]")
    base = t.replace("[]", "").strip()
    # map string
    if base == "string":
        base = "std::string"
    cpp_type = base
    for _ in range(arr_levels):
        cpp_type = f"std::vector<{cpp_type}>"
    return cpp_type

# convert args: "a : Type, b : Type" -> "Type a, Type b"
def convert_args(argstr: str):
    argstr = argstr.strip()
    if argstr == "":
        return ""
    parts = [a.strip() for a in re.split(r'\s*,\s*', argstr) if a.strip()]
    out = []
    for p in parts:
        # two common forms: "name : Type" or "Type name"
        m = re.match(r"([A-Za-z_]\w*)\s*:\s*(.+)", p)
        if m:
            name, atype = m.group(1), m.group(2)
            out.append(f"{convert_type(atype)} {name}")
        else:
            # fallback: split tokens and try to detect
            toks = p.split()
            if len(toks) == 1:
                out.append(p)  # unknown single token
            else:
                # assume last is name, rest is type
                name = toks[-1]
                atype = " ".join(toks[:-1])
                out.append(f"{convert_type(atype)} {name}")
    return ", ".join(out)

# 4) Patterns plus permissifs pour attr / method
# attribute: optional visibility, name : type
attr_re = re.compile(r"^([+-])?\s*([A-Za-z_]\w*)\s*:\s*(.+)$")
# method: optional visibility, name(args) [: return] OR name(args) return
method_re1 = re.compile(r"^([+-])?\s*([A-Za-z_]\w*)\s*\((.*?)\)\s*:\s*(.+)$")  # with colon return
method_re2 = re.compile(r"^([+-])?\s*([A-Za-z_]\w*)\s*\((.*?)\)\s*(\w[\w\[\]]*)?$")  # optional trailing return token

# parse class bodies
for cname, info in classes.items():
    for ln in info["lines"]:
        if DEBUG:
            print(f"[{cname}] parsing line: '{ln}'")
        m_attr = attr_re.match(ln)
        if m_attr:
            vis, aname, atype = m_attr.groups()
            vis = vis if vis else "+"
            info["attrs"].append((vis, aname.strip(), atype.strip()))
            continue
        m_m1 = method_re1.match(ln)
        if m_m1:
            vis, mname, args, ret = m_m1.groups()
            vis = vis if vis else "+"
            info["methods"].append((vis, mname.strip(), args.strip(), ret.strip()))
            continue
        m_m2 = method_re2.match(ln)
        if m_m2:
            vis, mname, args, ret = m_m2.groups()
            vis = vis if vis else "+"
            # if ret is None, set void
            ret = ret.strip() if ret else "void"
            info["methods"].append((vis, mname.strip(), args.strip(), ret))
            continue
        # if arrives here, line not parsed as attr/method. try to salvage: detect '(' anywhere
        if "(" in ln and ")" in ln:
            # best-effort: parse name before '('
            try:
                before, after = ln.split("(", 1)
                name_tok = before.strip().split()[-1]
                args = after.split(")",1)[0].strip()
                # try find return after ':' or last token
                ret = "void"
                if ":" in ln:
                    ret = ln.split(":",1)[1].strip()
                else:
                    # attempt trailing token
                    tail = ln.split(")",1)[1].strip()
                    if tail:
                        ret = tail.split()[-1]
                vis = "+"
                info["methods"].append((vis, name_tok, args, ret))
                if DEBUG:
                    print(f"  salvage method => {name_tok}({args}) : {ret}")
            except Exception as e:
                if DEBUG:
                    print("  salvage failed:", e)
        else:
            if DEBUG:
                print(f"  ignored line (not attr/method): '{ln}'")

# If debugging, show summary
if DEBUG:
    for cname, info in classes.items():
        print(f"\n== {cname} ==")
        print("attrs:")
        for a in info["attrs"]:
            print(" ", a)
        print("methods:")
        for m in info["methods"]:
            print(" ", m)

# 5) Generate files
for cname, info in classes.items():
    hpp_path = os.path.join(OUT_DIR, f"{cname}.hpp")
    cpp_path = os.path.join(OUT_DIR, f"{cname}.cpp")

    # determine includes
    need_string = any("string" in a[2] for a in info["attrs"]) or any("string" in (m[3] or "") for m in info["methods"]) or any("string" in (m[2] or "") for m in info["methods"])
    need_vector = any("[]" in a[2] for a in info["attrs"]) or any("[]" in (m[3] or "") for m in info["methods"]) or any("[]" in (m[2] or "") for m in info["methods"])
    parent = parent_of.get(cname)
    has_children = (cname in children_of)

    with open(hpp_path, "w", encoding="utf-8") as hpp:
        hpp.write("#pragma once\n\n")
        if need_string:
            hpp.write("#include <string>\n")
        if need_vector:
            hpp.write("#include <vector>\n")
        if parent:
            hpp.write(f'#include "{parent}.hpp"\n')
        if need_string or need_vector or parent:
            hpp.write("\n")
        inherit = f" : public {parent}" if parent else ""
        hpp.write(f"class {cname}{inherit}\n{{\npublic:\n")
        hpp.write(f"    {cname}();\n")
        if has_children:
            hpp.write(f"    virtual ~{cname}();\n")
        else:
            hpp.write(f"    ~{cname}();\n")
        # public attributes & methods
        for vis, aname, atype in info["attrs"]:
            if vis == "+":
                hpp.write(f"    {convert_type(atype)} {aname};\n")
        for vis, mname, args, ret in info["methods"]:
            if vis == "+":
                hpp.write(f"    {convert_type(ret)} {mname}({convert_args(args)});\n")
        hpp.write("\nprivate:\n")
        for vis, aname, atype in info["attrs"]:
            if vis == "-":
                hpp.write(f"    {convert_type(atype)} {aname};\n")
        for vis, mname, args, ret in info["methods"]:
            if vis == "-":
                hpp.write(f"    {convert_type(ret)} {mname}({convert_args(args)});\n")
        hpp.write("};\n")

    with open(cpp_path, "w", encoding="utf-8") as cpp:
        cpp.write(f'#include "{cname}.hpp"\n\n')
        cpp.write(f"{cname}::{cname}() {{}}\n")
        cpp.write(f"{cname}::~{cname}() {{}}\n\n")
        for vis, mname, args, ret in info["methods"]:
            cpp.write(f"{convert_type(ret)} {cname}::{mname}({convert_args(args)}) {{}}\n")

    print(f"Écrit: {hpp_path}  et  {cpp_path}")

print(f"\n✔ Génération terminée dans ./{OUT_DIR}/")
