# arduino_16relay_board
Control 16 Relay module(High level trigger) through UART with arduino and MCP23S17 chip.



UART MENU:
```
--- Command list: ---
? -> Print this HELP
RESET -> Reset contoller
STATUS -> Whole board status
ON_ALL -> Activate all ports
OFF_ALL -> Deactivate all port
port_#_on -> Port #(1-16) On  "activate"
port_#_off -> Port #(1-16) Off  "deactivate"
port_#_stat -> Port #(1-16) State  "status"
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
