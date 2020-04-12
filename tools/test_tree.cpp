#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

void test_3_full_layers() {
	/*         a
	          /  \
	        b     c
	       / \   / \
	      d  e  f  g
	*/
	TreeNode a = {0}, b = {0}, c = {0}, d = {0}, e = {0}, f = {0}, g = {0};
	a.left = &b;
	a.right = &c;
	b.left = &d;
	b.right = &e;
	b.val = 1;
	c.left = &f;
	c.right = &g;
	c.val = 2;
	d.val = 3;
	e.val = 4;
	f.val = 5;
	g.val = 6;

	vector<int> v = tree2vector(&a);
	vector<int> exp({0,1,2,3,4,5,6});
	if (v == exp)
		printf("%s succeeded\n", __func__);
	else
		printf("%s failed: tree2vector returned %s but expected %s\n",
			__func__, array2str(v).c_str(), array2str(exp).c_str());
}

void test_3_layers0() {
	/*         a
	          /  \
	        b     c
	       /     / \
	      d     f  g
	*/
	TreeNode a = {0}, b = {0}, c = {0}, d = {0}, f = {0}, g = {0};
	a.left = &b;
	a.right = &c;
	b.left = &d;
	b.val = 1;
	c.left = &f;
	c.right = &g;
	c.val = 2;
	d.val = 3;
	f.val = 5;
	g.val = 6;

	vector<int> v = tree2vector(&a);
	vector<int> exp({0,1,2,3,-1,5,6});
	if (v == exp)
		printf("%s succeeded\n", __func__);
	else
		printf("%s failed: tree2vector returned %s but expected %s\n",
			__func__, array2str(v).c_str(), array2str(exp).c_str());
}

void test_3_layers1() {
	/*         a
	          /  \
	        b     c
	       /       \
	      d        g
	*/
	TreeNode a = {0}, b = {0}, c = {0}, d = {0}, g = {0};
	a.left = &b;
	a.right = &c;
	b.left = &d;
	b.val = 1;
	c.right = &g;
	c.val = 2;
	d.val = 3;
	g.val = 6;

	vector<int> v = tree2vector(&a);
	vector<int> exp({0,1,2,3,-1,-1,6});
	if (v == exp)
		printf("%s succeeded\n", __func__);
	else
		printf("%s failed: tree2vector returned %s but expected %s\n",
			__func__, array2str(v).c_str(), array2str(exp).c_str());
}

void test_3_layers2() {
	/*         a
	          /  \
	        b     c
	       / \     \
	      d  e      g
	*/
	TreeNode a = {0}, b = {0}, c = {0}, d = {0}, e = {0}, g = {0};
	a.left = &b;
	a.right = &c;
	b.left = &d;
	b.right = &e;
	b.val = 1;
	c.right = &g;
	c.val = 2;
	d.val = 3;
	e.val = 4;
	g.val = 6;

	vector<int> v = tree2vector(&a);
	vector<int> exp({0,1,2,3,4,-1,6});
	if (v == exp)
		printf("%s succeeded\n", __func__);
	else
		printf("%s failed: tree2vector returned %s but expected %s\n",
			__func__, array2str(v).c_str(), array2str(exp).c_str());
}

void test_3_layers3() {
	/*         a
	          /  \
	        b     c
	       / \
	      d  e
	*/
	TreeNode a = {0}, b = {0}, c = {0}, d = {0}, e = {0};
	a.left = &b;
	a.right = &c;
	b.left = &d;
	b.right = &e;
	b.val = 1;
	c.val = 2;
	d.val = 3;
	e.val = 4;

	vector<int> v = tree2vector(&a);
	vector<int> exp({0,1,2,3,4});
	if (v == exp)
		printf("%s succeeded\n", __func__);
	else
		printf("%s failed: tree2vector returned %s but expected %s\n",
			__func__, array2str(v).c_str(), array2str(exp).c_str());
}

void test_3_layers4() {
	/*         a
	          /  \
	        b     c
	         \
	         e
	*/
	TreeNode a = {0}, b = {0}, c = {0}, e = {0};
	a.left = &b;
	a.right = &c;
	b.right = &e;
	b.val = 1;
	c.val = 2;
	e.val = 4;

	vector<int> v = tree2vector(&a);
	vector<int> exp({0,1,2,-1,4});
	if (v == exp)
		printf("%s succeeded\n", __func__);
	else
		printf("%s failed: tree2vector returned %s but expected %s\n",
			__func__, array2str(v).c_str(), array2str(exp).c_str());
}

void test_3_layers5() {
	/*         a
	          /
	        b
	         \
	         e
	*/
	TreeNode a = {0}, b = {0}, e = {0};
	a.left = &b;
	b.right = &e;
	b.val = 1;
	e.val = 4;

	vector<int> v = tree2vector(&a);
	vector<int> exp({0,1,-1,-1,4});
	if (v == exp)
		printf("%s succeeded\n", __func__);
	else
		printf("%s failed: tree2vector returned %s but expected %s\n",
			__func__, array2str(v).c_str(), array2str(exp).c_str());
}

void test_3_layers6() {
	/*         a
	            \
	             c
	              \
	               g
	*/
	TreeNode a = {0}, c = {0}, g = {0};
	a.right = &c;
	c.right = &g;
	c.val = 2;
	g.val = 6;

	vector<int> v = tree2vector(&a);
	vector<int> exp({0,-1,2,-1,6});
	if (v == exp)
		printf("%s succeeded\n", __func__);
	else
		printf("%s failed: tree2vector returned %s but expected %s\n",
			__func__, array2str(v).c_str(), array2str(exp).c_str());
}

void test_3_layers7() {
	/*         a
	            \
	             c
	            /
	           f
	*/
	TreeNode a = {0}, c = {0}, f = {0};
	a.right = &c;
	c.left = &f;
	c.val = 2;
	f.val = 5;

	vector<int> v = tree2vector(&a);
	vector<int> exp({0,-1,2,5});
	if (v == exp)
		printf("%s succeeded\n", __func__);
	else
		printf("%s failed: tree2vector returned %s but expected %s\n",
			__func__, array2str(v).c_str(), array2str(exp).c_str());
}

int main(int __attribute__(( unused )) argc,
	char __attribute__(( unused )) **argv) {

	test_3_full_layers();
	test_3_layers0();
	test_3_layers1();
	test_3_layers2();
	test_3_layers3();
	test_3_layers4();
	test_3_layers5();
	test_3_layers6();
	test_3_layers7();
	return 0;
}
