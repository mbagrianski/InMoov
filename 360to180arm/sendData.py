import serial

port = "/dev/ttyUSB0"

s1 = serial.Serial(port, 9600)
s1.flushInput()
running = True
while running:
    # read one byte of input from the serial buffer
    # input = s1.read(1)
    # print(ord(input))


    degree = int(input())

    if degree == -1:
        running = False
    #converts degree into bytes because serial.write() only accepts bytes
    encode_degree = b'degree'
    print (encode_degree)

    #write the bytes to the port
    s1.write(encode_degree)



    # s1.write(ord(input))
    # print (ord(input))

