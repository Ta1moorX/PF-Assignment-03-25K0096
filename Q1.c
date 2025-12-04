#include <stdio.h>

float calculateRepayment(float loan, float interestRate, int years, int currentYear, float totalPaid)
{
    // base case: if no year are left or the loan is paid off
    if (years == 0 || loan <= 0)
    {
        printf("\nTotal amount repaid: %.2f\n", totalPaid);
        return totalPaid;
    }

    float interest = loan * (interestRate / 100.0); /* */
    
    float newLoan = loan + interest;

    float installment = loan / years;

    float remaining = newLoan - installment;

    printf("Year %d: Remaining loan = %.2f\n", currentYear, remaining);

    // recurive case: calculate for next year
    return calculateRepayment(remaining, interestRate, years - 1, currentYear + 1, totalPaid + installment);
}
/*
Recursion keeps its own state per call (loan, year, total paid),
auto tracks progress via the call stack, processes one year per call,
and simplifies logic by avoiding loops and manual state tracking.
*/

// extended function logically similar to calculateRepayment for extra payments
float calculateRepaymentExtra(float loan, float interestRate, int years, int currentYear, float totalPaid, float extraPayment)
{
    if (years == 0 || loan <= 0)
    {
        printf("\nTotal amount repaid with extra payments: %.2f\n", totalPaid);
        return totalPaid;
    }

    float interest = loan * (interestRate / 100.0);
    float newLoan = loan + interest;
    float installment = loan / years;
    float totalPayment = installment + extraPayment;
    float remaining = newLoan - totalPayment;

    if (remaining < 0)
        remaining = 0;

    printf("Year %d: Payment = %.2f (Extra: %.2f), Remaining = %.2f\n",
           currentYear, totalPayment, extraPayment, remaining);

    return calculateRepaymentExtra(remaining, interestRate, years - 1, currentYear + 1, totalPaid + totalPayment, extraPayment);
}
// Recursion mirrors yearly dependency, passing updated loan/years/total each step.
// Easy to extend without major rewrites.
// Logic flows like real repayment: pay this year, recurse for the rest.
// Base cases cleanly handle early payoff or full term completion.
// Naturally applies compound interest using the updated loan each year.

int main()
{
    float loan = 100000;
    float rate = 5.0;
    int years = 3;

    printf("\nLoan Repayment Schedule:\n");
    printf("Initial Loan: %.2f\n", loan);
    printf("Interest Rate: %.2f%%\n", rate);
    printf("Years: %d\n\n", years);

    calculateRepayment(loan, rate, years, 1, 0);

    printf("\nWith Extra Payments:\n");
    calculateRepaymentExtra(loan, rate, years, 1, 0, 5000);

    return 0;
}