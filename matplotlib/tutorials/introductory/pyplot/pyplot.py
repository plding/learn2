#!/usr/bin/env python3
import matplotlib.pyplot as plt
import numpy as np

# first 
plt.figure()

t = np.arange(0, 5, 0.2)
plt.plot(t, t, "r--", t, t ** 2, "bs", t, t ** 3, "g^")

# scatter
plt.figure()

data = {"a": np.arange(50),
        "c": np.random.randint(0, 50, 50),
        "d": np.random.randn(50)}
data["b"] = data["a"] + 10 * np.random.randn(50)
data["d"] = np.abs(data["d"]) * 100

plt.scatter("a", "b", c="c", s="d", data=data)
plt.xlabel("entry a")
plt.ylabel("entry b")

# group
plt.figure(figsize=(9, 3))

names  = ["group_a", "group_b", "group_c"]
values = [1, 10, 100]

plt.subplot(131)
plt.bar(names, values)
plt.subplot(132)
plt.scatter(names, values)
plt.subplot(133)
plt.plot(names, values)
plt.suptitle("Categorical Plotting")

# axis
plt.figure()

def f(t):
    return np.exp(-t) * np.cos(2 * np.pi * t)

t1 = np.arange(0, 5, 0.1)
t2 = np.arange(0, 5, 0.02)

plt.subplot(211)
plt.plot(t1, f(t1), "bo", t2, f(t2), "k")
plt.subplot(212)
plt.plot(t2, np.cos(2 * np.pi * t2), "r--")

# text
plt.figure()

mu, sigma = 100, 15
x = mu + sigma * np.random.randn(10000)

n, bins, patches = plt.hist(x, 50, density=1, facecolor="g", alpha=0.75)

plt.xlabel("Smarts")
plt.ylabel("Probability")
plt.title("Histogram of IQ")
plt.text(60, .025, r"$\mu=100,\ \sigma=15$")
plt.axis([40, 160, 0, .03])
plt.grid(True)

# annotate
plt.figure()

t = np.arange(0, 5, 0.01)
s = np.cos(2 * np.pi * t)

plt.plot(t, s, lw=2)
plt.annotate("local max", xy=(2, 1), xytext=(3, 1.5),
             arrowprops={"facecolor": "black", "shrink": 0.05})
plt.ylim(-2, 2);

plt.show()
