#include "Python.h"

#include "math.h"
#include "numpy/ndarraytypes.h"
#include "numpy/ufuncobject.h"
#include "numpy/npy_3kcompat.h"


/* The loop definition must precede the PyMODINIT_FUNC. */

static void test(char **args, npy_intp *dimensions, npy_intp* steps, void* extra)
{
    npy_intp i;
    npy_intp n = dimensions[0];
	double tmp1;

    /* char�^�Ŏ󂯂�B                                                                   */
    /* �Ⴆ�΁Adouble�^�Ŏ󂯂�ƃX�g���C�h��8������̂ŁAin1 += in1_step�����܂������Ȃ� */
    char *in1 = args[0];
    char *out = args[1];

    /* �Ⴆ�΁Ain1 = x[::-1] �� �X�g���C�h��-8�Ȃ̂ŁA����in1[1]�ȂǂŃA�N�Z�X����Ƃ��܂������Ȃ� */
    npy_intp in1_step = steps[0];    /* input1�z��̗v�f�̃X�g���C�h  */
    npy_intp out_step = steps[1];    /* output�z��̗v�f�̃X�g���C�h  */


    printf("in_step = %d, out_step = %d\n", in1_step, out_step);
    for (i = 0; i < n; i++) {
		/*BEGIN main ufunc computation*/
		tmp1 = *(double *)in1;

        *((double *)out) = 2 * tmp1;
		/*END main ufunc computation*/
        
		in1 += in1_step;
		out += out_step;
    }
}

static void double_cum_pv_e(char **args, npy_intp *dimensions, npy_intp* steps, void* extra)
{
    npy_intp i;
    npy_intp n = dimensions[0];
	double tmp1, tmp2, cum;

    char *in1 = args[0];	/* �L���b�V���E�t���[ */
    char *in2 = args[1];	/* ���� */
    char *out = args[2];

    npy_intp in1_step = steps[0];    /* input1�z��̗v�f�̃X�g���C�h  */
    npy_intp in2_step = steps[1];    /* input2�z��̗v�f�̃X�g���C�h  */
    npy_intp out_step = steps[2];    /* output�z��̗v�f�̃X�g���C�h  */

	/* �z��̍Ō�̗v�f�Ɉړ� */
	in1 += in1_step * (n-1);
	in2 += in2_step * (n-1);
	out += out_step * (n-1);

    cum = 0.0;
    for (i = 0; i < n; i++) {
		/*BEGIN main ufunc computation*/
		tmp1 = *(double *)in1;
		tmp2 = *(double *)in2;

		cum = (cum + tmp1) / (1.0 + tmp2);
        *((double *)out) = cum;
		/*END main ufunc computation*/
        
        /* �z��̌�납��O�ɐi�� */
		in1 -= in1_step;
		in2 -= in2_step;
		out -= out_step;
    }
}


static void double_cum_pv_s(char **args, npy_intp *dimensions, npy_intp* steps, void* extra)
{
    npy_intp i;
    npy_intp n = dimensions[0];
	double tmp1, tmp2, cum;

    char *in1 = args[0];	/* �L���b�V���E�t���[ */
    char *in2 = args[1];	/* ���� */
    char *out = args[2];

    npy_intp in1_step = steps[0];    /* input1�z��̗v�f�̃X�g���C�h  */
    npy_intp in2_step = steps[1];    /* input2�z��̗v�f�̃X�g���C�h  */
    npy_intp out_step = steps[2];    /* output�z��̗v�f�̃X�g���C�h  */

	/* �z��̍Ō�̗v�f�Ɉړ� */
	in1 += in1_step * (n-1);
	in2 += in2_step * (n-1);
	out += out_step * (n-1);

    cum = 0.0;
    for (i = 0; i < n; i++) {
		/*BEGIN main ufunc computation*/
		tmp1 = *(double *)in1;
		tmp2 = *(double *)in2;

		cum = tmp1 + cum / (1.0 + tmp2);
        *((double *)out) = cum;
		/*END main ufunc computation*/
        
        /* �z��̌�납��O�ɐi�� */
		in1 -= in1_step;
		in2 -= in2_step;
		out -= out_step;
    }
}


/*This a pointer to the above function*/
PyUFuncGenericFunction funcs0[1] = {&test};
PyUFuncGenericFunction funcs1[1] = {&double_cum_pv_e};
PyUFuncGenericFunction funcs2[1] = {&double_cum_pv_s};

/* These are the input and return dtypes of logit.*/
static char types2[2] = {
	NPY_DOUBLE,    /* input1  */
	NPY_DOUBLE     /* output1 */
};

static char types3[3] = {
	NPY_DOUBLE,    /* input1  */
	NPY_DOUBLE,    /* input2  */
	NPY_DOUBLE     /* output1 */
};

static void *data[1] = {NULL};

static PyMethodDef Methods[] = {
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "ufunc",
    NULL,
    -1,
    Methods,
    NULL,
    NULL,
    NULL,
    NULL
};

PyMODINIT_FUNC PyInit_ufunc(void)
{
    PyObject *m, *d;
    PyObject *myfunc, *myfunc1, *myfunc2;

    m = PyModule_Create(&moduledef);
    if (!m) {
        return NULL;
    }
    import_array();
    import_umath();

    d = PyModule_GetDict(m);

	/* test�̓o�^ */
    myfunc = PyUFunc_FromFuncAndData(
    	funcs0,
    	data,
    	types2,                
    	1,                    /* �T�|�[�g����^�̐� */
    	1,                    /* inputs�̐�         */
    	1,                    /* outputs�̐�        */
    	PyUFunc_None,
    	"test",               /* �o�^�����֐��� */
        "test_docstring",
        0
    );

    PyDict_SetItemString(d, "test", myfunc);
    Py_DECREF(myfunc);

	/* cum_pv_e�̓o�^ */
    myfunc1 = PyUFunc_FromFuncAndData(
    	funcs1,
    	data,
    	types3,                
    	1,                    /* �T�|�[�g����^�̐� */
    	2,                    /* inputs�̐�         */
    	1,                    /* outputs�̐�        */
    	PyUFunc_None,
    	"cum_pv_e",             /* �o�^�����֐��� */
        "x1:cashflow, x2:forwardrate\ncashflow is assumed at the end of month.\nfor(i=n-1;i>=0;i--)\n    pv[i] = (cf[i+1] + pv[i+1]) / (1 + forward[i])",
        0
    );

    PyDict_SetItemString(d, "cum_pv_e", myfunc1);
    Py_DECREF(myfunc1);

	/* cum_pv_e�̓o�^ */
    myfunc2 = PyUFunc_FromFuncAndData(
    	funcs2,
    	data,
    	types3,                
    	1,                    /* �T�|�[�g����^�̐� */
    	2,                    /* inputs�̐�         */
    	1,                    /* outputs�̐�        */
    	PyUFunc_None,
    	"cum_pv_s",             /* �o�^�����֐��� */
        "x1:cashflow, x2:forwardrate\ncashflow is assumed at the start of month.\nfor(i=n-1;i>=0;i--)\n    pv[i] = cf[i+1] + pv[i+1] / (1 + forward[i])",
        0
    );

    PyDict_SetItemString(d, "cum_pv_s", myfunc2);
    Py_DECREF(myfunc2);

    return m;
}
