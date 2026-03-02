// Daniel Beddingfield
// Shakeel
// CS 210
// 8 Feb 2026

// ======== Class "InterestCalculator" ========

// Declares InterestCalculator class
#ifndef INTEREST_CALCULATOR_INTEREST_CALCULATOR_H_
#define INTEREST_CALCULATOR_INTEREST_CALCULATOR_H_

#include <iostream>

class InterestCalculator
{
public:
    // Constructor: initializes program values
    InterestCalculator();

    // Starts the program flow
    void run();

private:

    void dataInput();       // Collects initial data from the user

    void results();         // Displays results tables and handles menu options

    void calculateNoDeposits();     // Calculates one month of interest without monthly deposits
    void calculateWithDeposits();   // Calculates one month of interest with monthly deposits

    void inputValidation(int t_menuId); // Verifies input values are valid; throws an exception if invalid

    // Variables
    int m_numYears;
    int m_yearCount;
    int m_resultsInput;

    double m_initialInvestment;
    double m_monthlyDeposit;
    double m_annualInterest;

    double m_eoyResults;
    double m_eoyResultsDeposit;

    bool m_validInput;
};

#endif