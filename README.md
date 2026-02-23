# numeria-streaming-optimizer
An $O(1)$ space complexity solution to the Numeria resource equalization problem, developed as a streaming algorithm during a timed quiz.   

## problem
In the Kingdom of Numeria, a grand festival is being celebrated. To mark the occasion, the ruler has decided to increase the resources of all residents so that everyone ends up with the same amount.

There are $n$ residents in Numeria. The current amount of resources owned by the $i$-th resident is given as an integer $b_i$ coins.

You are the chief accountant of the kingdom. Your task is to determine the smallest total number of coins that must be distributed so that all residents have equal resources. The ruler is only allowed to give coins — taking coins away from anyone is strictly forbidden.

### input
- The first line contains a single integer $n$ $(1 \le n \le 100)$ — the number of residents.
- The second line contains $n$ integers $b_1, b_2, \dots, b_n$, where $b_i$ $(0 \le b_i \le 10^6)$ represents the current amount of coins held by the $i$-th resident.

### output
- Print a single integer $T$ — the minimum total number of coins that must be distributed so that all residents have equal amounts.
In the Kingdom of Numeria, the ruler wants to equalize the wealth of $n$ residents. As the Chief Accountant, you must find the **minimum** total coins to distribute so that everyone matches the balance of the wealthiest resident. 

## first thought
When first faced with this, the "obvious" solution that came to my mind is a **two-pass approach** using an array ($O(n)$ space):
1.  **Pass 1:** Read all $n$ values into an array to identify the global maximum ($b_{max}$).
2.  **Pass 2:** Iterate through that array again to calculate the sum of differences: $\sum (b_{max} - b_i)$.

## second thought
Why waste memory allocating arrays just to iterate through two separate loops? Since the goal is simply to find the difference between a global maximum and a cumulative sum, I realized I could calculate everything in real-time as the data is being read. This streaming approach ensures the memory footprint remains constant $O(1)$ regardless of the input size.

(Actually, I was just lazy enough to avoid the extra lines of code needed for array management and a second loop.)

## solution
Developed during a timed quiz, this solution uses **Streaming Logic** to solve the problem in a single pass with **zero array storage**.

By reframing the problem with a single-pass mathematical identity, I kept the memory footprint at a constant $O(1)$:

$$\text{Total Distributed} = (n \times \text{max}) - \sum b$$

**logic:**
* **Smart Initialization:** Instead of arbitrary defaults, I read the first resident's wealth and immediately set it as both the initial `max` and the starting `sum`.
* **Streaming Update:** By starting the loop from the second resident ($i=1$), I avoid adding the first input twice while tracking the global maximum and running total simultaneously.
* **$O(1)$ Space Complexity:** I store only a few primitive variables. Whether the kingdom has 10 residents or 10 million, the memory footprint remains constant.
* **Integer Safety:** I utilized `1LL` literal multipliers and `long long` accumulators to prevent 32-bit integer overflow in case of larger datasets where the product $(n \times \text{max})$ or the cumulative sum $\sum b_i$ exceeds $2^{31}-1$.

## code
```c
#include <stdio.h>

int main() {
    int n, b, x;
    long long s;

    // Read number of residents
    scanf("%d", &n);
    
    // Initialize max (x) and sum (s) with the first resident
    scanf("%d", &x);
    s = x;

    for(int i = 1; i < n; i++) {
        scanf("%d", &b);
        s += b; // Track running sum
        if(b > x)
        x = b; // Track running maximum
    }

    // Mathematical Shortcut: (number of residents * max wealth) - Current Total
    printf("%lld\n", (1LL * n * x) - s);

    return 0;
}
