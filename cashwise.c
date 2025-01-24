#include <stdio.h>
#include <stdlib.h>

struct Finance {
    float expenditures;
    float income;     
    float stocks;
    float savings;
    float emis;       
    float rents;      
};

float percentage_change(float previous, float current) {
    if (previous == 0) return current > 0 ? 100 : 0;
    return ((current - previous) / previous) * 100;
}

void display_and_store_report(struct Finance prev_month, struct Finance curr_month, FILE *file) {
    fprintf(file, "\nMonthly Finance Report:\n");
    fprintf(file, "\nCategory         Previous Month   Current Month   Change(%%)\n");
    fprintf(file, "------------------------------------------------------------\n");

    fprintf(file, "Income :         %.2f            %.2f            %.2f%%\n", prev_month.income, curr_month.income,
           percentage_change(prev_month.income, curr_month.income));
    fprintf(file, "Expenditures:    %.2f            %.2f            %.2f%%\n", prev_month.expenditures, curr_month.expenditures,
           percentage_change(prev_month.expenditures, curr_month.expenditures));
    fprintf(file, "Stocks:          %.2f            %.2f            %.2f%%\n", prev_month.stocks, curr_month.stocks,
           percentage_change(prev_month.stocks, curr_month.stocks));
    fprintf(file, "Savings:         %.2f            %.2f            %.2f%%\n", prev_month.savings, curr_month.savings,
           percentage_change(prev_month.savings, curr_month.savings));
    fprintf(file, "EMIs:            %.2f            %.2f            %.2f%%\n", prev_month.emis, curr_month.emis,
           percentage_change(prev_month.emis, curr_month.emis));
    fprintf(file, "Rents:           %.2f            %.2f            %.2f%%\n", prev_month.rents, curr_month.rents,
           percentage_change(prev_month.rents, curr_month.rents));

    printf("\nReport saved to file successfully.\n");
}

int read_previous_month(struct Finance *prev_month, FILE *file) {
    if (fscanf(file, "%f %f %f %f %f %f", &prev_month->expenditures, &prev_month->income, 
               &prev_month->stocks, &prev_month->savings, &prev_month->emis, &prev_month->rents) != 6) {
        return 0;
    }
    return 1;
}

void store_current_month(struct Finance curr_month, FILE *file) {
    fprintf(file, "%.2f %.2f %.2f %.2f %.2f %.2f\n", curr_month.expenditures, curr_month.income, curr_month.stocks,
            curr_month.savings, curr_month.emis, curr_month.rents);
}

void provide_suggestions(struct Finance prev_month, struct Finance curr_month) {
    printf("\n** Financial Suggestions **\n");
    if (curr_month.savings > prev_month.savings) {
        printf("Your savings have increased this month! Keep up the good work. Consider investing or saving more.\n");
    } else if (curr_month.savings < prev_month.savings) {
        printf("Your savings have decreased. Try reviewing your spending and look for ways to save more.\n");
    }
    
    if (curr_month.emis > prev_month.emis) {
        printf("Your EMIs have increased. You may want to explore options for refinancing or paying off high-interest loans.\n");
    }

    if (curr_month.expenditures > prev_month.expenditures) {
        printf("Your expenditures are higher. It's a good time to track your spending and identify areas to cut back.\n");
    }
}

FILE* open_or_create_file(const char *filename, const char *mode) {
    FILE *file = fopen(filename, mode);
    if (!file) {
        printf("Error opening file %s. Creating a new one...\n", filename);
        file = fopen(filename, "w");
        if (!file) {
            printf("Error creating file %s!\n", filename);
            exit(1);
        }
    }
    return file;
}

int main() {
    struct Finance prev_month = {0, 0, 0, 0, 0, 0}, curr_month;
    FILE *file, *report_file;

    file = open_or_create_file("financial_log.txt", "r");

    if (!read_previous_month(&prev_month, file)) {
        printf("No previous month data found, initializing to zero values.\n");
    }
    fclose(file);

    printf("\n**** Enter Financial Details for the Current Month ****\n");
    printf("Please input the values for the following categories:\n");
    
    printf("\nIncome (e.g., 5000.00): ");
    scanf("%f", &curr_month.income);
    
    printf("Expenditures (e.g., 1500.00): ");
    scanf("%f", &curr_month.expenditures);
    
    printf("Stocks (e.g., 2000.00): ");
    scanf("%f", &curr_month.stocks);
    
    printf("Savings (e.g., 1000.00): ");
    scanf("%f", &curr_month.savings);
    
    printf("EMIs (e.g., 500.00): ");
    scanf("%f", &curr_month.emis); 
    
    printf("Rents (e.g., 800.00): ");
    scanf("%f", &curr_month.rents);

    printf("\nYou entered the following data for the current month:\n");
    printf("Income: %.2f, Expenditures: %.2f, Stocks: %.2f, Savings: %.2f, EMIs: %.2f, Rents: %.2f\n", 
            curr_month.income, curr_month.expenditures, curr_month.stocks, curr_month.savings, curr_month.emis, curr_month.rents);
    
    printf("\nIs this information correct? (Y/N): ");
    char confirmation;
    getchar();  
    scanf("%c", &confirmation);
    
    if (confirmation == 'N' || confirmation == 'n') {
        printf("Please restart the program to input the correct data.\n");
        return 0;
    }

    file = open_or_create_file("financial_log.txt", "a");
    store_current_month(curr_month, file);
    fclose(file);

    report_file = open_or_create_file("financial_status.txt", "a");
    display_and_store_report(prev_month, curr_month, report_file);
    fclose(report_file);

    provide_suggestions(prev_month, curr_month);

    return 0;
}
