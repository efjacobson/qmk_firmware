#! /bin/bash

cd "$HOME/dev/efjacobson/qmk_firmware/keyboards/keebio/quefrency/keymaps/efjacobson"
sed -i.bu 's/_______/KC_TRNS/g' keymap.c
qmk compile -kb keebio/quefrency/rev2
sed -i.bu 's/KC_TRNS/_______/g' keymap.c
rm keymap.c.bu