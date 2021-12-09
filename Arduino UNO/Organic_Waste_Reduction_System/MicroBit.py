def continous():
  bit_0 = pins.digital_read_pin(DigitalPin.P1);
  bit_1 = pins.digital_read_pin(DigitalPin.P0);
  
  if(bit_1 == 0 and bit_0 == 1):
    basic.show_leds("""
    . # # . .
    . . # . .
    . . # . .
    . . # . .
    . # # # .
    """);
  elif(bit_1 == 1 and bit_0 == 0):
    basic.show_leds("""
    # # # . .
    . . # . .
    # # # . .
    # . . . .
    # # # . .
    """);
  elif(bit_1 == 1 and bit_0 == 1):
    basic.show_leds("""
    # # # . .
    . . # . .
    # # # . .
    . . # . .
    # # # . .
    """);
  else:
    basic.show_leds("""
    # # # # .
    # . . # .
    # . . # .
    # . . # .
    # # # # .
    """);
    
    
  basic.pause(100);

basic.forever(continous)
