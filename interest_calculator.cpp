// Daniel Beddingfield
// Shakeel
// CS 210
// 8 Feb 2026

// ======== Main bulk of the program ========

// Implements the InterestCalculator class logic

#include "interest_calculator.h"

#include <iomanip>
#include <stdexcept>

using namespace std;

// Initializes all member variables
InterestCalculator::InterestCalculator()
    : m_numYears(0),
      m_yearCount(0),
      m_resultsInput(0),
      m_initialInvestment(0.0),
      m_monthlyDeposit(0.0),
      m_annualInterest(0.0),
      m_eoyResults(0.0),
      m_eoyResultsDeposit(0.0),
      m_validInput(false)
{
}

// Controls the overall program
void InterestCalculator::run()
{
    dataInput();
    results();
}

// Initial menu "Yearly Interest Calculator"
void InterestCalculator::dataInput()
{
    cout << "\n**********************************\n"
         << "*** Yearly Interest Calculator ***\n";

    m_validInput = false;

    // Loop until valid input is provided
    while (!m_validInput) {
        cout << "- Initial Investment: $";
        cin >> m_initialInvestment;

        cout << "- Monthly Deposit: $";
        cin >> m_monthlyDeposit;

        cout << "- Annual Interest: %";
        cin >> m_annualInterest;

        cout << "- Number of Years: ";
        cin >> m_numYears;

        // Validate input values
        try {
            inputValidation(1);
            m_validInput = true;
        }
        catch (const invalid_argument& t_ex) {
            cout << "[ERROR] " << t_ex.what() << "\n";
            m_validInput = false;
        }
    }
}

// Calculates interest for one month without deposits
void InterestCalculator::calculateNoDeposits()
{
    m_eoyResults = m_initialInvestment * ((m_annualInterest / 100.0) / 12.0);
}

// Calculates interest for one month with deposits
void InterestCalculator::calculateWithDeposits()
{
    m_eoyResultsDeposit =
        (m_initialInvestment + m_monthlyDeposit) * ((m_annualInterest / 100.0) / 12.0);
}

// Displays results tables and modify menu
void InterestCalculator::results()
{
    // Continue until the user chooses to exit
    while (m_resultsInput != 5) {

        // WITHOUT monthly deposits
        cout << "\n     Balance and Interest WITHOUT Additional Monthly Deposits\n"
             << "================================================================\n"
             << left
             << setw(6)  << "Year"
             << setw(22) << "Year End Balance"
             << "Year End Earned Interest\n"
             << "----------------------------------------------------------------\n";

        double startInvestment = m_initialInvestment;
        double balanceNoDep = startInvestment;

        m_yearCount = 0;

        // Loop for each year
        while (m_yearCount < m_numYears) {
            double interestThisYear = 0.0;

            // Calculate interest per month
            for (int month = 1; month <= 12; month++) {
                m_initialInvestment = balanceNoDep;
                calculateNoDeposits();
                balanceNoDep += m_eoyResults;
                interestThisYear += m_eoyResults;
            }

            // Increment year count, until m_yearCount > m_numYears
            m_yearCount++;

            cout << left
                 << setw(6) << m_yearCount
                 << "$" << setw(21) << fixed << setprecision(2) << balanceNoDep
                 << "$" << fixed << setprecision(2) << interestThisYear
                 << "\n";
        }

        // WITH monthly deposits
        cout << "\n     Balance and Interest WITH Additional Monthly Deposits\n"
             << "================================================================\n"
             << left
             << setw(6)  << "Year"
             << setw(22) << "Year End Balance"
             << "Year End Earned Interest\n"
             << "----------------------------------------------------------------\n";

        m_yearCount = 0;
        double balanceWithDep = startInvestment;

        // Loop through each year
        while (m_yearCount < m_numYears) {
            double interestThisYear = 0.0;

            // Calculate interest per month, including deposits
            for (int month = 1; month <= 12; month++) {
                balanceWithDep += m_monthlyDeposit;

                m_initialInvestment = balanceWithDep - m_monthlyDeposit;
                calculateWithDeposits();

                balanceWithDep += m_eoyResultsDeposit;
                interestThisYear += m_eoyResultsDeposit;
            }

            m_yearCount++;

            cout << left
                 << setw(6) << m_yearCount
                 << "$" << setw(21) << fixed << setprecision(2) << balanceWithDep
                 << "$" << fixed << setprecision(2) << interestThisYear
                 << "\n";
        }

        // Adjustment Menu
        cout << "\nWould you like to adjust any values?\n"
             << "1. Initial Investment Amount\n"
             << "2. Monthly Deposit Amount\n"
             << "3. Annual Interest Rate\n"
             << "4. Number of Years\n"
             << "5. Exit Program\n";
        cin >> m_resultsInput;

        // Handle menu selection and updating values
        switch (m_resultsInput) {
            case 1:
                cout << "Enter new Initial Investment Amount: $";
                cin >> m_initialInvestment;
                break;
            case 2:
                cout << "Enter new Monthly Deposit Amount: $";
                cin >> m_monthlyDeposit;
                break;
            case 3:
                cout << "Enter new Annual Interest Rate (%): ";
                cin >> m_annualInterest;
                break;
            case 4:
                cout << "Enter new Number of Years: ";
                cin >> m_numYears;
                break;
            case 5:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "[ERROR] Invalid selection. Please try again.\n";
        }

        // Re-validate values after modifications
        if (m_resultsInput != 5) {
            try {
                inputValidation(1);
            }
            catch (const invalid_argument& t_ex) {
                cout << "[ERROR] " << t_ex.what() << "\n";
                dataInput();
            }
        }
    }
}

// Checks input values for valid ranges
void InterestCalculator::inputValidation(int t_menuId)
{
    if (t_menuId == 1) {
        if (m_initialInvestment < 0.0)
            throw invalid_argument("Initial Investment must be >= 0.");

        if (m_monthlyDeposit < 0.0)
            throw invalid_argument("Monthly Deposit must be >= 0.");

        if (m_annualInterest < 0.0)
            throw invalid_argument("Annual Interest must be >= 0.");

        if (m_numYears <= 0 || m_numYears > 100)
            throw invalid_argument("Number of Years must be between 1 and 100.");
    }
}