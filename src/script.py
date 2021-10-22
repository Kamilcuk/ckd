#!/usr/bin/env python3
import sys
import re
import os
import jinja2


def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)


# https://groups.google.com/g/pocoo-libs/c/3yZl8vHJ9fI
# https://stackoverflow.com/questions/25449879/embed-custom-filter-definition-into-jinja2-template
def get_re_flags(flagstr):
    reflags = 0
    if flagstr:
        if flagstr.find("i") > -1:
            reflags |= re.IGNORECASE
        if flagstr.find("l") > -1:
            reflags |= re.LOCALE
        if flagstr.find("m") > -1:
            reflags |= re.MULTILINE
        if flagstr.find("s") > -1:
            reflags |= re.DOTALL
        if flagstr.find("u") > -1:
            reflags |= re.UNICODE
        if flagstr.find("x") > -1:
            reflags |= re.VERBOSE
    return reflags


def is_re_match(value, regex, flagstr=None):
    reflags = get_re_flags(flagstr)
    return not not re.search(regex, value, reflags)


def NISSIGNED(s):
    return isinstance(s, str) and len(s) > 0 and s[0] == "u"


inputfile = sys.argv.pop(1)
HAVE_UINT128 = int(sys.argv.pop(1))
outf = open(sys.argv.pop(1), 'w')

env = jinja2.Environment(
    loader=jinja2.FileSystemLoader(os.path.dirname(os.path.abspath(__file__))),
    autoescape=False,
    trim_blocks=True,
    lstrip_blocks=True
)
env.tests['is_re_match'] = is_re_match
env.tests['NISSIGNED'] = NISSIGNED

print(
    env.get_template(inputfile).render(
        HAVE_UINT128=HAVE_UINT128
    ),
    file=outf,
)
