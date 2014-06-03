# coding: cp932

import numpy as np
import ufunc as myuf

cf = np.array([100.0, 200.0, 300.0])
fwd = np.array([0.01, 0.02, 0.03])
print( myuf.cum_pv_s(cf, fwd) )
rslt = np.array([300, 300 / 1.02 + 200, (300 / 1.02 + 200) / 1.01 + 100])[::-1]
print(rslt)

print( myuf.cum_pv_e(cf, fwd) )
rslt = np.array([300 / 1.03, (300 / 1.03 + 200) / 1.02, ((300 / 1.03 + 200) / 1.02 + 100) / 1.01])[::-1]
print(rslt)

