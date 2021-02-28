# MCU name
MCU = atmega32u4

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = caterina

# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
NKRO_ENABLE = yes           # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
COMBO_ENABLE = yes
EXTRAKEY_ENABLE = yes       # Audio control and System control
TAP_DANCE_ENABLE = yes
OLED_DRIVER_ENABLE = yes
# UNICODE_ENABLE = yes        # Unicode
# BACKLIGHT_ENABLE = yes      # Enable keyboard backlight functionality
# BLUETOOTH_ENABLE = yes      # Enable Bluetooth with the Adafruit EZ-Key HID

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend
# BOOTMAGIC_ENABLE = no      # Virtual DIP switch configuration
# COMMAND_ENABLE = no        # Commands for debug and configuration
# CONSOLE_ENABLE = no        # Console for debug
# MIDI_ENABLE = no           # MIDI controls
# MOUSEKEY_ENABLE = no       # Mouse keys
