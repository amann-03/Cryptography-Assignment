Overview
This project implements a “prime computer” that computes the n‑th prime number using a simple prime detector based on trial division.

The goal is to mirror the idea of Willans’ formula (prime detector → prime computer), but in an algorithmic and computationally efficient way.

The program conceptually:

Reads an integer 
n
n.

Uses a trial‑division primality test as the prime detector.

Counts primes starting from 2 upwards until the 
n
n-th prime is reached.

Outputs the 
n
n-th prime (or an error if it does not fit in 64‑bit signed integers).

This realizes the same structure as Willans’ approach:

Prime detector ⇒ prime counter ⇒ nth‑prime computer,

but using trial division instead of Wilson’s theorem and trigonometric expressions.

Mathematical description
1. Prime detector via trial division
We define a detector 
D
(
x
)
D(x) that indicates whether an integer 
x
x is prime.

Definition:

For any integer 
x
x:

If 
x
<
2
x<2, then 
D
(
x
)
=
0
D(x)=0 (not prime).

If 
x
≥
2
x≥2 and there is no integer divisor 
d
d with

2
≤
d
≤
⌊
x
⌋
such that
d
∣
x
,
2≤d≤⌊ 
x
 ⌋such thatd∣x,
then 
D
(
x
)
=
1
D(x)=1 (x is prime).

Otherwise 
D
(
x
)
=
0
D(x)=0.

In logical form:

D
(
x
)
=
{
1
,
x
≥
2
 and 
∀
d
∈
{
2
,
…
,
⌊
x
⌋
}
,
 
d
∤
x
,
0
,
otherwise.
D(x)={ 
1,
0,
  
x≥2 and ∀d∈{2,…,⌊ 
x
 ⌋}, d∤x,
otherwise.
 
We can also express this with a product over potential divisors:

Let the indicator of divisibility be

I
(
d
∣
x
)
=
{
1
,
d
∣
x
,
0
,
d
∤
x
.
I(d∣x)={ 
1,
0,
  
d∣x,
d∤x.
 
Define

A
(
x
)
=
∏
d
=
2
⌊
x
⌋
(
1
−
I
(
d
∣
x
)
)
.
A(x)= 
d=2
∏
⌊ 
x
 ⌋
 (1−I(d∣x)).
Then:

If 
x
≥
2
x≥2 and no divisor 
d
d divides 
x
x, every factor in the product is 1, so 
A
(
x
)
=
1
A(x)=1.

If some 
d
d divides 
x
x, the corresponding factor is 
1
−
1
=
0
1−1=0, so 
A
(
x
)
=
0
A(x)=0.

Thus we can take:

D
(
x
)
=
{
A
(
x
)
,
x
≥
2
,
0
,
x
<
2.
D(x)={ 
A(x),
0,
  
x≥2,
x<2.
 
This 
D
(
x
)
D(x) is our trial‑division prime detector.

2. From detector to prime‑counting function 
π
(
x
)
π(x)
Given the detector 
D
(
x
)
D(x), we can define the prime‑counting function 
π
(
x
)
π(x), which counts how many primes are 
≤
x
≤x.

Definition:

π
(
X
)
=
∑
m
=
2
X
D
(
m
)
.
π(X)= 
m=2
∑
X
 D(m).
Each term 
D
(
m
)
D(m) is 1 if 
m
m is prime and 0 otherwise.

Therefore, 
π
(
X
)
π(X) is exactly the number of primes up to 
X
X.

Conceptually, the program is simulating this sum by:

Initializing a counter to 0.

Iterating 
m
=
2
,
3
,
4
,
…
m=2,3,4,….

For each 
m
m, updating

count
←
count
+
D
(
m
)
.
count←count+D(m).
At any point in the loop, the variable “count” is equal to 
π
(
m
)
π(m).

3. From prime counter to nth‑prime computer 
p
n
p 
n
 
We now use 
π
(
x
)
π(x) to define the 
n
n-th prime number 
p
n
p 
n
 .

Mathematically, the 
n
n-th prime is:

p
n
=
min
⁡
{
x
≥
2
:
π
(
x
)
=
n
}
.
p 
n
 =min{x≥2:π(x)=n}.
Using our detector, this means:

Start with 
x
=
2
x=2 and a counter 
c
=
0
c=0.

For each integer 
x
=
2
,
3
,
4
,
…
x=2,3,4,…:

Compute 
D
(
x
)
D(x) using trial division.

Update the count:

c
←
c
+
D
(
x
)
.
c←c+D(x).
Now 
c
=
π
(
x
)
c=π(x).

When 
c
=
n
c=n for the first time, we have 
x
=
p
n
x=p 
n
 .

So the algorithmic process is (in words):

Initialize:

x
←
1
x←1

c
←
0
c←0

Loop:

Increment candidate: 
x
←
x
+
1
x←x+1.

If 
D
(
x
)
=
1
D(x)=1, then 
c
←
c
+
1
c←c+1.

If 
c
=
n
c=n, stop and output 
x
x as 
p
n
p 
n
 .

This is precisely the “prime detector ⇒ prime counter ⇒ nth‑prime” pipeline, but implemented with trial division instead of Wilson’s theorem.

For completeness, you can also write an explicit, purely mathematical definition of 
p
n
p 
n
  using indicator functions:

Let 
D
(
x
)
D(x) be the trial‑division detector.

Let 
π
(
x
)
=
∑
m
=
2
x
D
(
m
)
π(x)=∑ 
m=2
x
 D(m).

Then:

p
n
=
∑
x
=
2
∞
x
⋅
I
(
π
(
x
)
=
n
 
∧
 
π
(
x
−
1
)
=
n
−
1
)
,
p 
n
 = 
x=2
∑
∞
 x⋅I(π(x)=n∧π(x−1)=n−1),
where 
I
(
⋅
)
I(⋅) is 1 if the condition is true, 0 otherwise. Only one term in this infinite sum is non‑zero: where 
x
=
p
n
x=p 
n
 .

4. Edge cases and limits
Conceptually, the implementation takes into account:

Invalid 
n
n:

If 
n
≤
0
n≤0, the “
n
n-th prime” is not defined, so the procedure is considered invalid.

Positivity:

The counting process starts from 
x
=
2
x=2 because primes are defined for integers 
≥
2
≥2.

Machine limits:

In practice, integers are bounded (for example, 64‑bit signed integers up to 
2
63
−
1
2 
63
 −1).

If the loop reaches the maximum representable integer before the 
n
n-th prime is found, the program terminates with an error instead of overflowing.

These considerations make the implementation robust from a systems point of view, even though mathematically primes go on forever.

5. Complexity analysis and comparison to Willans’ formula
Complexity of the trial‑division nth‑prime computer
The detector 
D
(
x
)
D(x) tests all potential divisors up to 
x
x
 .

This is 
O
(
x
)
O( 
x
 ) work per candidate 
x
x.

To find 
p
n
p 
n
 , the algorithm examines all integers from 2 up to approximately 
p
n
p 
n
 .

From the prime number theorem:

p
n
∼
n
log
⁡
n
as 
n
→
∞
.
p 
n
 ∼nlognas n→∞.
Total work is roughly:

∑
x
=
2
p
n
O
(
x
)
=
O
(
p
n
3
/
2
)
≈
O
(
(
n
log
⁡
n
)
3
/
2
)
.
x=2
∑
p 
n
 
 O( 
x
 )=O(p 
n
3/2
 )≈O((nlogn) 
3/2
 ).
If we optimize trial division by dividing only by previously found primes, a classical analysis yields about 
O
(
n
2
)
O(n 
2
 ) operations to generate the first 
n
n primes. In any case, this is polynomial in 
n
n.

Complexity of Willans’ formula
Willans’ formula for the 
n
n-th prime:

Uses an outer summation up to approximately 
2
n
2 
n
 .

For each 
i
i in this sum, it has an inner summation in 
j
j and a term derived from Wilson’s theorem involving factorials and trigonometric functions.

Roughly:

The outer loop runs 
O
(
2
n
)
O(2 
n
 ) times.

The inner work per 
i
i is at least proportional to 
i
i, giving a total cost on the order of:

∑
i
=
1
2
n
i
=
O
(
4
n
)
,
i=1
∑
2 
n
 
 i=O(4 
n
 ),
ignoring the enormous cost and growth of factorials.

Therefore, evaluating Willans’ formula grows super‑polynomially in 
n
n, effectively exponential in the index 
n
n, and quickly becomes infeasible for modest 
n
n.

Comparison
Trial‑division method:

Roughly 
O
(
(
n
log
⁡
n
)
3
/
2
)
O((nlogn) 
3/2
 ) time.

Practically workable for quite large 
n
n.

Willans’ formula:

Time grows like 
O
(
4
n
)
O(4 
n
 ) (or similar), dominated by extremely large sums and factorials.

Becomes unusable even for relatively small 
n
n.

Thus, while both approaches are built on the same conceptual pattern (prime detector wrapped into a prime computer), the trial‑division‑based method is computationally vastly superior and much more realistic for an implementation in C++.
