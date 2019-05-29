# arduino with MCP23S17 16 port relay board control
 - Script friendly command interface via serial port
 - Ambient Temperature sensor (ds18b20)
 - Control 16 Relay module(High level trigger) through MCP23S17 chip.



UART MENU:
```
--- Command list: ---
? -> Print this HELP
port * on  -> Activate all ports
port * off  -> Deactivate all port
port * stat  -> All ports status
port # on  -> Port #(1-16) On  "activate"
port # off  -> Port #(1-16) Off  "deactivate"
port # stat  -> Port #(1-16) State  "status"
reset -> Reset Arduino controller
temp -> Show Ambient temperature "C"
---
```

UART STATUS PAGE:
```
--- STATUS: ---
port=1,status=0
port=2,status=0
port=3,status=0
port=4,status=0
port=5,status=0
port=6,status=0
port=7,status=0
port=8,status=0
port=9,status=0
port=10,status=0
port=11,status=0
port=12,status=0
port=13,status=0
port=14,status=0
port=15,status=0
port=16,status=0
```
