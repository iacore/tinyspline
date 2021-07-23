#include <testutils.h>

#ifdef _MSC_VER
#pragma warning(push)
/* unreferenced label */
#pragma warning(disable:4102)
#endif

void free_bspline(CuTest* tc)
{
	___SETUP___
	tsBSpline spline;

	___GIVEN___
	ts_bspline_new(10, 2, 2, TS_CLAMPED, &spline, &status);
	CuAssertPtrNotNull(tc, spline.pImpl);

	___WHEN___
	ts_bspline_free(&spline);

	___THEN___
	CuAssertPtrEquals(tc, spline.pImpl, NULL);

	___TEARDOWN___
}

void free_deboornet(CuTest* tc)
{
	___SETUP___
	tsBSpline spline;
	tsDeBoorNet net;

	___GIVEN___
	ts_bspline_new(10, 2, 2, TS_CLAMPED, &spline, &status);
	ts_bspline_eval(&spline, 0, &net, &status);
	CuAssertPtrNotNull(tc, net.pImpl);

	___WHEN___
	ts_deboornet_free(&net);

	___THEN___
	CuAssertPtrEquals(tc, net.pImpl, NULL);

	___TEARDOWN___
	ts_bspline_free(&spline);
}

CuSuite* get_free_suite()
{
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, free_bspline);
	SUITE_ADD_TEST(suite, free_deboornet);
	return suite;
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
