#!/usr/bin/env python3
import os
import sys

import jinja2

env = jinja2.Environment(
    loader=jinja2.FileSystemLoader(os.path.dirname(os.path.abspath(__file__))),
    undefined=jinja2.StrictUndefined,
    autoescape=False,
    trim_blocks=True,
    lstrip_blocks=True,
)

args = sys.argv
inputfile = args.pop(1)
outf = open(args.pop(1), "w")
for aa in sys.argv[1:]:
    tt = aa.split("=")
    env.globals[tt[0]] = tt[1]

print(
    env.get_template(inputfile).render(),
    file=outf,
)
