# CONSOLE_ENABLE = yes

SRC += efjacobson.c

# Disable unused features to save on space
# https://thomasbaart.nl/2018/12/01/reducing-firmware-size-in-qmk/
MOUSEKEY_ENABLE   = no # 2000 bytes
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
COMMAND_ENABLE    = no # https://beta.docs.qmk.fm/features/feature_command
UNICODE_ENABLE    = no  # Unicode
SWAP_HANDS_ENABLE = no  # Allow swapping hands of keyboard
# https://www.reddit.com/r/olkb/comments/bmpgjm/programming_help/
# Should shave 2000 bytes
LTO_ENABLE = yes
