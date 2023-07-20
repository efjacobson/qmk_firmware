#! /bin/bash

qmk_root=
case "$(hostname)" in
neuraspire)
    qmk_root="$HOME/._/dev/git/efjacobson/qmk_firmware"
    ;;
WTMZ-TMZ006298)
    qmk_root="$HOME/dev/efjacobson/qmk_firmware"
    ;;
*) ;;
esac

[ -z "$qmk_root" ] && echo 'do where now?' && exit
cd "$qmk_root" || exit
keymap="$qmk_root/keyboards/keebio/quefrency/keymaps/efjacobson/keymap.c"

sed -i.bu 's/_______/KC_TRNS/g' "$keymap"

secret="$(cat secret)"
if [ "$(uname)" == 'Darwin' ]; then
    sed -i '' "s/SUPER_SRSLY_SECRET_YALL/$secret/g" "$keymap"
else
    sed -i "s/SUPER_SRSLY_SECRET_YALL/$secret/g" "$keymap"
fi

make keebio/quefrency/rev2:efjacobson:flash
mv "$keymap.bu" "$keymap"
