actlib_numpy
============

numpy custom ufunc for Actuaries

the following ufuncs are implemented.
 
- cum_pv_e

  - Recursive present value of cashflow at the end of the period.
  - input x1:cashflow, x2:forwardrate

  - Equivalent code:
    for(i=n-1;i>=0;i--)
        pv[i] = (x1[i+1] + pv[i+1]) / (1 + x2[i])


- cum_pv_s

  - Recursive present value of cashflow at the start of the period.
  - input x1:cashflow, x2:forwardrate

  - Equivalent code:
    for(i=n-1;i>=0;i--)
        pv[i] = x1[i+1] + pv[i+1] / (1 + x2[i])

