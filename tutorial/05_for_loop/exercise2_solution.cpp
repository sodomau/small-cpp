void SmallMain()
  {
      int number = InputInt("Table (2 to 9): ");
      for (int i = 1; i <= 9; i = i + 1)
      {
          Print(number, " x ", i, " = ", number * i);
      }
  }
