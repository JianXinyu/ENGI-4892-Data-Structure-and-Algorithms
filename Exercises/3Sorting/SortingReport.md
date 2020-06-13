### Exercises for 27 May

1. Implement the `insertionSort` function in [sorting.h](https://memorialu.gitlab.io/Engineering/ECE/Teaching/data-structures/website/modules/sorting/exercises/sorting.h).

2. Analyze the worst-case run-time performance of the merge sort. **Hint:** use the recursive definition of the merge sort to describe the run time of the merge sort for N values (i.e., T(N)), then you may find a [telescoping sum](https://en.wikipedia.org/wiki/Telescoping_series) to be helpful. If you need some extra hints (**after** attempting it yourself), take a look at p306 of the textbook and/or try watching the [video](https://youtu.be/PR0thkPFYfA).

    Apparently, T(1) = 1

    $$T(n)=n+2T(\frac{n}{2})$$

    We can find that:

    $T(n)=kn+2^kT(\frac{n}{2^k})$

    $T(n)=nlog_2n+nT(1)$

    so the worst-case run-time performance of the merge sort is $nlog_2n+n$.

3. [optional] Analyze the worst-case run-time performance of your insertion sort. **Hint:** the answer should be $O(n^2)$, **even if** the way you designed your algorithm has a doubly-nested `for` loop.

   ![image-20200530203054370](C:\Users\jianx\AppData\Roaming\Typora\typora-user-images\image-20200530203054370.png)

   For $i$th iteration of the first for loop, there will be 3 assignment operations outside the while loop, and $i*(2 compare operations + 1 logical operation + 1 assignment operation + arithmetic operation)$ inside the while loop.

    $\sum_{i=1}^{n} i=1+2+3+\cdots+n=\frac{n(n+1)}{2}$

   Thus, $T(n)=3n+4\frac{n(n+1)}{2}=O(n^2)$



### Exercises for 29 May 

1. Implement the radix sort for integers using a function template and *specialize* your template for strings.

   see function radixSort() and radixSortString() in "sorting.h"

2. [optional] Change the code above to simply `cout << uniqueNames << "\n";`. Implement whatever operator functions are required to make this work.

   skip

3. [optional] Implement the counting/bucket sort for integers.

   skip

















