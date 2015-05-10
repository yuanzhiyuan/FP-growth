# FP-growth
An implementation of FP-growth by JiaWei Han's paper.

# Example
Given six transations:<br>
transation1: a,b,d,e <br>
transation2: b,c,e<br>
transation3: a,b,d,e<br>
transation4: a,b,c,e<br>
transation5: a,b,c,d,e<br>
transation6: b,c,d<br>
<br>
And a min support 3<br>
<br>
output:<br>
e,c     3<br>
b,c     4<br>
b,e,c   3<br>
b,d     4<br>
e,d     3<br>
b,e,d   3<br>
e,a     4<br>
e,a,d   3<br>
b,e,a,d 3<br>
b,e,a   4<br>
b,a     4<br>
a,d     3<br>
b,a,d   3<br>
b,e     5<br>
