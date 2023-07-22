#!/bin/bash
set -euo pipefail

r() {
	echo "+ $*" >&2
	"$@"
}

DIR="$(dirname "$(readlink -f "$0")")"/..
cd "$DIR"
inc=_build/default/include
cmd="$*"
if [[ -z "$cmd" ]]; then
	echo "ERROR: no args" >&2
	exit 1
fi
if [[ "$cmd" =~ ^ckd_ ]]; then
	cmd="$(cat <<EOF
__auto_type r = $cmd;
printf("$cmd=");
_Generic(r, int: printf("%d", r), ckd_int_t: printf("%d overflow=%d", ckd_value(r), ckd_overflow(r)));
printf("\\n");
EOF
	)"
fi
script="\
#include <ckdint.h>
#include <assert.h>
#include <stdio.h>
int main() {
$cmd
}"
: "${CC:=cc}"
trap 'rm -f ./a.out' EXIT
cat -n <<<"$script"
r "$CC" -I"$inc" -xc - <<<"$script" && ./a.out
r "$CC" -I"$inc" -DCKD_NOGNU_SOURCE=1 -xc - <<<"$script" && ./a.out
