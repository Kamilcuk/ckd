#!/bin/bash
set -euo pipefail

cachedir=${BASH_SOURCE[0]%/*}/../_build/measure

if (($# == 1)) && [[ "$1" == "output" ]]; then
    prev="$cachedir"/prev

    if [[ -e "$prev" ]]; then
        echo "--- previous"
        cat "$prev"
        echo "--- current"
    fi

    {
        echo "   Top time:"
        sort -k3nr "$cachedir"/*.txt | head -n 5 | column -t
        echo "   Top MEM:"
        sort -k5nr "$cachedir"/*.txt | head -n 5 | column -t
        f() {
			local count
            count=$(
				g++ -E ./tests/"$1".c -DCKD_NOGNU_SOURCE=1 -I./_build/default/include/ |
                wc
			)
			countfmt=$(numfmt --to=iec --field - <<<"$count")
            printf "%s\t%s\t%s\n" "$1" "$count" "$countfmt"
        }
		echo
		{
			f test_more3
			f test_mixing3
		} | {
			if hash column 2>/dev/null; then
				column -t -N file,lines,words,chars,lines,words,chars
			else
				cat
			fi
		}
    } | tee "$cachedir"/tmp
    mv "$cachedir"/tmp "$cachedir"/prev
    exit
fi
# Otherwise executed from CMake with compiler command line.

suffix=
if [[ "$*" = *CKD_NOGNU_SOURCE* ]]; then
	suffix="_nognu"
fi
# shellcheck disable=2124
file="${@: -1}"
file="${file##*/}"
file="${file%%.c}"
file="$file$suffix"
mkdir -p "$cachedir"
if [[ ! -e /usr/bin/time ]]; then
    TIMEFORMAT=$'%Uuser\t%Ssystem\t%Relapsed\t%PCPU\t-1MEM\t'"$file"
    # http://mywiki.wooledge.org/BashFAQ/032
    exec 3>&1 4>&2
    { time "$@" 1>&3 2>&4; } 2> >(tee "$cachedir/$file.txt" >&2)
else
    /usr/bin/time -f $'%Uuser\t%Ssystem\t%eelapsed\t%PCPU\t%MMEM\t'"$file" -o "$cachedir/$file.txt" "$@"
    cat "$cachedir/$file.txt" >&2
fi


