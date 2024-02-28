# AlmostRandom

AlmostRandom is a random number generator for Arduino.


# Updates

- 0.10.0
	- Finished implementing most methods.
- 0.6.0
    - Implemented Ranalog methods.

# Disclaimer

This library is meant for educational and recreational use only, do not use the random numbers generated by this library for critical and high-stake use cases like encryption and important decisions.

There maybe inaccurate or incomplete information regarding random numbers, like their nature, generation, usage and testing methods. I seek your forgiveness and understanding as I am not an expert in random numbers or microcontrollers.


# Random Numbers
There are generally two kinds of random numbers: true random or pseudo-random. Some examples of true random sources include radioactive decay, atmospheric electrical noises and some quantum phenomena. They are not the easiest to harvest and processed into random numbers in a typical home setting.

As such, for non-critical tasks, pseudo-random numbers are used. They are often generated from a formula using a seed as a starting condition. 

An example of such formula is the Middle-Square method. If `123` is used as a seed and squared, the answer will be `15129`. We can then extract the middle three digits of `15129`to use as our random number, which will be `512`. `512` can then be used as a seed for the next random number.

One commonly used seed is the Unix Time, or the number of seconds passed since 1 January 1970, which has the advantage of being unique every second.

One major problem with pseudo-random numbers is that if one knows the seed and the formula, you can predict the outcome. Poor formula may also result in pseudo-random number looping in a sequence.

There are also methods that are in-between. A coin toss may seem random but if one knows all the initial conditions for the toss, they will be able to predict the outcome. However due to how unpredictable and chaotic a casual coin toss is, it is practically random for a day-to-day non-critical use case. This library aim to deliver such numbers between true and pseudo-random. 


## Ranalog: Mix things up for analogRead()!
The reading from analogRead() has been a staple to use as a seed for the Arduino built-in random number generator. It usually goes like this:
```
randomSeed( analogRead(A0) );
long randNumber = random(10, 10000);
Serial.println(randNumber);
```
The idea is a floating (unconnected) pin will measure surround electromagnetic interference (EMI) to produce a random reading. However, calling `analogRead()` 10,000 times and plotting the readings seems to tell a different story:

![image](extras/analogRead_Frequency_(No_Antenna).jpg)

It seems like less than half of the possible values from 0 to 1023 were produced at least once, and there is a discernible 'U' shape with spikes at the end. This may not even make for a good seed.

Out of curiosity, I decided to look at the parity of the readings. It means seeing how many of the readings are odd and how many are even:

![](extras/analogRead_Parity_(No_Antenna).jpg)

Throughout three sets of 10,000 readings, the ratios of odd to even number come close to 50:50. This effectively makes the parity of `analogRead()` a coin toss. A bit can be a one or zero, so if the microcontroller unit (MCU) "toss" this coin eight times, it would be able to produce one random byte (eight bits in one byte).

I dub this the "Ranalog" method and this is how the distribution looks like:

![](extras/Ranalog_Frequency_(No_Antenna).jpg)

I supposed that extending the pin with a wire will make it into an antenna, and hopefully this antenna will be able to pick up EMI more randomly, as such, I attached a 6.5 and 10.0cm antenna via a breadboard:

![](extras/Ranalog_Frequency_(6.5cm_Antenna).jpg)
![](extras/Ranalog_Frequency_(10.0cm_Antenna).jpg)

And finally, I stuck eight antenna of different length, one to each pin:

![](extras/Ranalog_Frequency_(Multi_Antennae).jpg)






## Ramdom: Chaotic RAM

## Ranclock: The Clock Jitters

## Rainput: Imprecise Humans

## AmostRandom: Altogether Now!



# Public Functions
## AlmostRandom()

Constructor to initialise values. 


##  _byte_ getRandomByte()

Get a random number as a byte, from 0 to 255.

