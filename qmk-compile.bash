#! /bin/bash

qmk_root=
case "$(hostname)" in
NeurAspire)
  qmk_root="$HOME/._/dev/git/efjacobson/qmk_firmware"
  ;;
WTMZ-TMZ006298)
  qmk_root="$HOME/dev/efjacobson/qmk_firmware"
  ;;
*) ;;
esac

[ -z "$qmk_root" ] && echo 'do where now?' && exit

cd "$qmk_root/keyboards/keebio/quefrency/keymaps/efjacobson"
sed -i.bu 's/_______/KC_TRNS/g' keymap.c
cd "$qmk_root"
make keebio/quefrency/rev2:efjacobson:flash
cd "$qmk_root/keyboards/keebio/quefrency/keymaps/efjacobson"
sed -i.bu 's/KC_TRNS/_______/g' keymap.c
rm keymap.c.bu
