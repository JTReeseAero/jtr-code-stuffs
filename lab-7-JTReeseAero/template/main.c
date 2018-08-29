double integrand(double x){
    // Your test fucntion goes here
    return x*x;
}

// Forword declaration of function prototypes here

int main(void) {
    double ans;

    ans = midpoint(integrand, 0, 2);
    printf("Midpoint integration: %g\n", ans);

    ans = simpson_13(integrand, 0, 2);
    printf("Simpson's 1/3 Rule: %g\n", ans);

    ans = simpson_38(integrand, 0, 2);
    printf("Simpson's 3/8 Rule: %g\n", ans);

    ans = gauss_quad(integrand, 0, 2, 3);
    printf("Gauss Quad: %g\n", 0, 2);

    return 0;
}
