void SmallMain()
  {
      int age = InputInt("Age: ");
      if (age <= 12)
      {
          Print("Child");
      }
      else if (age <= 19)
      {
          Print("Teenager");
      }
      else
      {
          Print("Adult");
      }
  }
