#include <bits/stdc++.h>
using namespace std;

// Function to Calculate GCD
int computeGCD(int a, int b) 
{
    a = abs(a);
    b = abs(b);

    // Using Loop ->
    while (b) 
    {
        a %= b;
        swap(a, b);
    }
    return a;

    // Using Recursion ->
    // if(b == 0)
    //     return a;
    // else
    //     return computeGCD(b, a%b);
}

// GCD of a List of Numbers 
// Works on the Fact that GCD(a,b,c) = GCD(GCD(a,b),c)
int computeGCDofList(const vector<int>& nums) 
{
    int result = nums[0];
    for (int i = 1; i < nums.size(); i++) 
    {
        result = computeGCD(result, nums[i]);
    }
    return result;
}

// Generate all combinations of size k using Backtracking
void generateCombinations(int start, int k, vector<int>& current, const vector<int>& input, vector<vector<int>>& combinations) 
{
    if (current.size() == k) 
    {
        combinations.push_back(current);
        return;
    }

    for (int i = start; i < input.size(); i++) 
    {
        current.push_back(input[i]);
        generateCombinations(i + 1, k, current, input, combinations);
        current.pop_back();
    }
}

void quickSort(vector<int>& arr, int low, int high) 
{
    if (low >= high) return;

    int pivot = arr[high];  // choosing the last element as pivot
    int i = low - 1;

    for (int j = low; j < high; j++) 
    {
        if (arr[j] > pivot) // Use '>' for Descending and '<' for Ascending Order
        { 
            ++i;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);

    int pivotIndex = i + 1;
    quickSort(arr, low, pivotIndex - 1);
    quickSort(arr, pivotIndex + 1, high);
}

// Call Quick Sort from this Function
void sortCoordinates(vector<int>& coords) 
{
    quickSort(coords, 0, coords.size() - 1);
}





// Condition 1 for Flips in 3 and N Dimension
bool condition1(const vector<int>& coords) 
{
    int n = coords.size();
    int k = n - 1;

    vector<vector<int>> allCombinations;
    vector<int> current;

    generateCombinations(0, k, current, coords, allCombinations);

    for (const auto& combo : allCombinations) 
    {
        if (computeGCDofList(combo) != 1) 
            return false;  // At least One Combination has GCD Not Equal to 1
    }

    return true;
}

// Condition 2 for Flips in 3 and N Dimension
bool condition2(const vector<int>& coords) 
{
    int sum = 0;
    for(int i = 0; i < coords.size(); i++)
    {
        sum += coords[i];
    }

    if(sum <= 0)
        return false;
    else
        return true;
}    

// Function to Create Combinations and Check for Conditions for a Fixed Number for Condition 3
bool isFixValid(int fixed, const vector<int>& rest) 
{
    if (fixed == 1) 
        return true;

    // Generate All Combinations of 2 elements in 'rest'
    for (int i = 0; i < rest.size() - 1; i++) 
    {
        for (int j = i + 1; j < rest.size(); j++) 
        {
            int sum = rest[i] + rest[j];
            sum = abs(sum);
            int other = 0;

            for (int k = 0; k < rest.size(); k++) 
            {
                if (k != i && k != j) 
                {
                    other = rest[k];
                    break;
                }
            }

            if (sum % fixed == 0 && computeGCD(fixed, other) == 1)
                return true;
        }
    }
    return false;
}

// Condition 3 for Flips in 3 Dimension
bool condition3_3D(const vector<int>& coords) 
{
    vector<int> abs_coords = coords;

    // for (int& x : abs_coords) 
    //    x = abs(x);

    // Fix every number one by one and create a vector of the other 3 elements and send them for Checking
    for (int i = 0; i < abs_coords.size(); i++) 
    {
        if(abs_coords[i] > 0)
        {
            int fixed = abs_coords[i];        
            vector<int> rest;

            for (int j = 0; j < abs_coords.size(); j++)
            {
                if (i != j)
                    rest.push_back(abs_coords[j]);
            }

            if (!isFixValid(fixed, rest))
                return false;
        }
    }

    return true;
}

bool condition3_nD(const vector<int>& coords) 
{
    int n = coords.size();

    for (int i = 0; i < n; i++) 
    {
        int ai = coords[i];

        if (ai <= 0) 
            break;  // Only check for positive ai
        if (ai == 1) 
            continue;  // Optimization: Always passes when a_i is 1

        // Loop over all k from 1 to a_i - 1
        for (int k = 1; k < ai; k++) 
        {
            long long sum = 0;

            for (int j = 0; j < n; j++) 
            {
                if (j == i) 
                    continue;

                int aj = coords[j];
                int mod1 = aj % ai;

                if (mod1 < 0) 
                    mod1 += ai;  // Handle Negative a_j or Mod value

                int term = (mod1 * k) % ai;
                sum += term;
            }

            if (sum <= ai) 
            {
                // Fails condition at this a_i and k
                cout << "\nCondition 3 Failed at i = " << i << " (a_i = " << ai << "), for k = " << k << ", sum = " << sum << endl;
                return false;
            }
        }
    }

    return true;  // All positive a_i passed all k values
}





// Function to Check for Flips in 3 Dimension
bool checkFlipsin_3D(const vector<int>& coords) 
{
    bool allPassed = true;

    if (!condition1(coords)) 
    {
        cout << "\nCondition 1 Failed: GCD is Not 1 for Some Combination" << endl;
        allPassed = false;
    }

    if (!condition2(coords)) 
    {
        cout << "\nCondition 2 Failed: Sum <= 0" << endl;
        allPassed = false;
    }

    if (!condition3_3D(coords)) 
    {
        cout << "\nCondition 3 Failed: No Valid Modulo or GCD Combination Found" << endl;
        allPassed = false;
    }

    return allPassed;
}

// Function to Check for Flips in 3 Dimension
bool checkFlipsin_nD(const vector<int>& coords) 
{
    bool allPassed = true;

    if (!condition1(coords)) 
    {
        cout << "\nCondition 1 Failed: GCD is Not 1 for Some Combination" << endl;
        allPassed = false;
    }

    if (!condition2(coords)) 
    {
        cout << "\nCondition 2 Failed: Sum <= 0" << endl;
        allPassed = false;
    }

    if (!condition3_nD(coords)) 
    {
        allPassed = false;
    }

    return allPassed;
}

int main() 
{
    int n;
    cout << "Enter number of coordinates (n): ";
    cin >> n;

    // Check if number of Co-ordinates is Valid or Not
    if (n <= 3) 
    {
        cout << "Insufficient Number of Coordinates: " << n <<endl;
        return 0;
    }
    
    vector<int> coords(n);
    cout << "Enter the " << n << " numbers (coordinates): ";

    for (int i = 0; i < n; i++) 
    {
        cin >> coords[i];
    }

    int negCount = 0;

    for (int i = 0; i < n; i++) 
    {
        if(coords[i] < 0)
        {
            negCount += 1;
        }
    }

    if(negCount < 2)
    {
        cout<<"\nThere should be atleast 2 Negative Co-ordinates\n";
    }

    bool valid = true;
    int boundary = 0;
    boundary = n / 2; // Will have to Modify this Formula based on different Dimensions
    
    for (int i = 0; i < n; i++) 
    {
        if (n % 2 == 0)
        {
            if(i < boundary && coords[i] < 0)
            {
                cout << "\nCo-ordinate at Index " << i + 1 << " should be Positive" <<endl;
                valid = false;
            }
            else if(i >= boundary && coords[i] > 0)
            {
                cout << "\nCo-ordinate at Index " << i + 1 << " should be Negative" <<endl;
                valid = false;
            }
        }
        else
        {
            if(i < boundary && coords[i] < 0)
            {
                cout << "\nCo-ordinate at Index " << i + 1 << " should be Positive" <<endl;
                valid = false;
            }
            else if(i > boundary && coords[i] > 0)
            {
                cout << "\nCo-ordinate at Index " << i + 1 << " should be Negative" <<endl;
                valid = false;
            } 
        }
    }

    if (!valid) 
    {
        cout << "\nAborting program due to Invalid Co-ordinate Input\n" <<endl;
        return 0;
    }

    sortCoordinates(coords); // Sort using Quick Sort Technique

    // Call the Function based on the Number of Co-ordinates Received
    if (n == 4) 
    {
        bool passed = checkFlipsin_3D(coords);
        if (passed) 
            cout << "\n3D Flip: All Conditions Satisfied\n" << endl;
        else 
            cout << "\n3D Flip: One or More Conditions Failed\n" << endl;
    }
    else if (n > 4) 
    {
        bool passed = checkFlipsin_nD(coords);
        if (passed) 
            cout << "\nn-D Flip: All Conditions Satisfied\n" << endl;
        else 
            cout << "\nn-D Flip: One or More Conditions Failed\n" << endl;
    }

    return 0;
}
