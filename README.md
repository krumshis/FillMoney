###__Coin Sums__###   
####_problem #31_####    
In England the currency is made up of pound, £, and pence, p, and there are eight coins in general circulation: 1p, 2p, 5p, 10p, 20p, 50p, £1 (100p) and £2 (200p). It is possible to make £2 in the following way: 1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p.   
How many different ways can £2 (200p) be made using any number of coins?

The solution is a recursive function. It doesn't print combinations of coins, just counts combinations that add up to £2 (200p). We sort coins in descending order and start from the biggest coin, trying to make a combination.

**The answer is 73,682 different combinations.**
