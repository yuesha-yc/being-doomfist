![](cover.png)

# Being Doomfist is better than playing Doomfist

Controlling your Overwatch character with electromyography sensors (EMG).

This is a project participating [CalHacks - Hello:World](https://helloworld.calhacks.io/)

View our progress and gallery at [Devpost](https://devpost.com/software/being-doomfist-is-better-than-playing-doomfist)


# Brief Explain

We use the [Myoware Muscle Sensor](https://www.sparkfun.com/products/13723) to read the electrical signals from three muscle groups. The analog voltage value is then captured with the Tequila Nano controller board. Then, the 14-bit analog values are send to the USART port alone with the state of a push button.

On the PC side, we use Python to read the data received from the USART port, and then apply a threshold to determine whether a certain action is activated. If the signal is above threshold, we will use `win32api` and `windll` to simulate keyboard and mouse events. These events will be registered by Overwatch, thus achieve the successful control of the Doomfist character.


### Credits (names in alphabetical order)

[Haocheng Yang](https://github.com/bill-the-sci-guy): Hardware implementation

[Yichen Wang](https://github.com/yuesha-yc): Software implementation

[Yifei Li](https://github.com/LiYifei1218): Software implementation

[-T.K.-](https://github.com/T-K-233): Hardware & software implementation

