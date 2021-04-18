import datetime as dt
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import random

# Create figure for plotting
fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
xs = []
y1s = []
y2s = []



# This function is called periodically from FuncAnimation
def animate(i, xs, y1s, y2s):

    # Read temperature (Celsius) from TMP102
    temp_c = random.random()
    temp_c2 = random.random()

    # Add x and y to lists
    xs.append(dt.datetime.now().strftime('%H:%M:%S.%f'))
    y1s.append(temp_c)
    y2s.append(temp_c2)

    # Limit x and y lists to 20 items
    xs = xs[-20:]
    y1s = y1s[-20:]
    y2s = y2s[-20:]

    # Draw x and y lists
    ax.clear()
    ax.plot(xs, y1s)
    ax.plot(xs, y2s)

    # Format plot
    plt.xticks(rotation=45, ha='right')
    plt.subplots_adjust(bottom=0.30)
    plt.title('TMP102 Temperature over Time')
    plt.ylabel('Temperature (deg C)')

# Set up plot to call animate() function periodically
ani = animation.FuncAnimation(fig, animate, fargs=(xs, y1s, y2s), interval=10)
plt.show()
