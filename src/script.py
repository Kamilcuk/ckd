#!/usr/bin/env python3
import sys
import os
import jinja2

inputfile = sys.argv.pop(1)
HAVE_UINT128 = int(sys.argv.pop(1))
outf = open(sys.argv.pop(1), 'w')

env = jinja2.Environment(
    loader=jinja2.FileSystemLoader(os.path.dirname(os.path.abspath(__file__))),
    undefined=jinja2.StrictUndefined,
    autoescape=False,
    trim_blocks=True,
    lstrip_blocks=True
)
env.globals['HAVE_UINT128'] = HAVE_UINT128

print(
    env.get_template(inputfile).render(),
    file=outf,
)
