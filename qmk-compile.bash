#! /bin/bash

display_help() {
  echo "
Available options:
  --no-flash  - If you want to open the list of pull requests
   -n
  --help      - This message
   -h
"
}

flash='true'

for opt in "$@"; do
  case ${opt} in
  --no-flash)
    flash='false'
    ;;
  *)
    display_help
    exit 1
    ;;
  esac
done

self="${BASH_SOURCE[0]}"
while [ -L "${self}" ]; do
    self_dir="$(cd -P "$(dirname "${self}")" >/dev/null 2>&1 && pwd)"
    self="$(readlink "${self}")"
    [[ ${self} != /* ]] && self="${self_dir}/${self}"
done
self="$(readlink -f "${self}")"
qmk_root=$(dirname "${self}")

[ -z "${qmk_root}" ] && echo 'do where now?' && exit
cd "${qmk_root}" || exit
keymap="${qmk_root}/keyboards/keebio/quefrency/keymaps/efjacobson/keymap.c"

sed -i.bu 's/_______/KC_TRNS/g' "${keymap}"

if [ -e "${qmk_root}/.secret" ]; then
    secret="$(cat "${qmk_root}/.secret")"
else
    printf 'enter secret: '
    if ! read -rs secret; then
        echo 'fail:read:secret'
        exit 1
    fi
    printf '\n'
    read -r -p 'save secret to file? [y/N] ' save
    if [[ "${save}" =~ ^[Yy](es)?$ ]]; then
        echo "${secret}" >"${qmk_root}/.secret"
    fi
fi

if [ "$(uname)" == 'Darwin' ]; then
    sed -i '' "s/SUPER_SRSLY_SECRET_YALL/${secret}/g" "${keymap}"
else
    sed -i "s/SUPER_SRSLY_SECRET_YALL/${secret}/g" "${keymap}"
fi

if [ "${flash}" == 'true' ]; then
    make keebio/quefrency/rev2:efjacobson:flash
else
    make keebio/quefrency/rev2:efjacobson
fi

mv "${keymap}.bu" "${keymap}"
