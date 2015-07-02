#include	<stdlib.h>
#include	<stdbool.h>
#include	<stdio.h>
#include	<assert.h>

#define		__DEBUG__

#define		MEMO_SIZE	1000000

long long	memo[MEMO_SIZE];	

typedef struct	s_collatz_test_case
{
  char		*name;
  long long	value;
  long long	expected_result;
}		t_collatz_test_case;

t_collatz_test_case	collatz_cases[] = {
  {"test collatz : one", 1, 4},
  {"test collatz : two", 2, 1},
  {"test collatz : three", 3, 10},
  {"test collatz : four", 4, 2},
  {"test collatz : five", 5, 16},
  {"test collatz : one hundred", 100, 50},
  {NULL, 0, 0}
};

t_collatz_test_case collatz_sequence_length_cases[] = {
  {"test collatz length : one", 1, 1},
  {"test collatz length : two", 2, 2},
  {"test collatz length : three", 3, 8},
  {NULL, 0, 0}
};

t_collatz_test_case collatz_max_sequence_starter_cases[] = {
  {"test collatz max sequence starter : one", 1, 1},
  {"test collatz max sequence starter : two", 2, 2},
  {"test collatz max sequence starter : three", 3, 3},
  {"test collatz max sequence starter : four", 4, 3},
  {"test collatz max sequence starter : five", 5, 3},
  {"test collatz max sequence starter : six", 6, 6},
  {"test collatz max sequence starter : seven", 7, 7},
  {"test collatz max sequence starter : eight", 8, 7},
  {"test collatz max sequence starter : nine", 9, 9},
  {"test collatz max sequence starter : ten", 10, 9},
  {NULL, 0, 0}
};

void		init_memo(long long *tab)
{
  int		i;

  for (i = 0; i < MEMO_SIZE; i++)
    {
      tab[i] = -1;
    }
}

bool		is_even(long long n)
{
  return (n % 2 == 0);
}

long long	collatz(long long n)
{
  long long	result;

  if (is_even(n))
    {
      result = n / 2;
    }
  else 
    {
      result = n * 3 + 1;
    }
  return (result);
}

long long	collatz_sequence_length(long long n)
{
  long long	length;
  long long	value;

  if (n == 1)
    {
      return (1);
    }
  else if (memo[n] != -1)
    {
      printf("memo[%lld] => (%lld)\n", n, memo[n]);
      return (memo[n]);
    }
  else
    {
      length = 1;
      value = collatz(n);
      while (value != 1)
	{
	  value = collatz(value);
	  length++;
	}
      memo[n] = length + 1;
      return (length + 1);
    }
}

long long	collatz_max_sequence_starter(long long  n, long long current_starter)
{
  long long	max_index;
  long long	max_length;
  long long	tmp;
  long long	value;

  max_length = 0;
  max_index = 0;
  for (value = 1; value <= n; value++)
    {
      tmp = collatz_sequence_length(value);
      if (tmp > max_length)
	{
	  max_index = value;
	  max_length = tmp;
	}
    }
  printf("{%lld} : ", max_index);
  printf("{%lld}\n", max_length);
  return (max_index);
}

void		test_init_memo()
{
  int		i;

  init_memo(memo);
  for (i = 0; i < MEMO_SIZE; i++)
    {
      assert(memo[i] == -1);
    }
}

void		test_collatz(t_collatz_test_case *current_case)
{
  char		*name;
  long long	value;
  long long	expected_result;

  name = current_case->name;
  if (name != NULL)
    {
      puts(name);
      value = current_case->value;
      expected_result = current_case->expected_result;
      assert(collatz(value) == expected_result);
      test_collatz(current_case + 1);
    }
}

void		test_collatz_sequence_length(t_collatz_test_case *current_case)
{
  char		*name;
  long long	value;
  long long	expected_result;

  name = current_case->name;
  if (name != NULL)
    {
      puts(name);
      value = current_case->value;
      expected_result = current_case->expected_result;
      assert(collatz_sequence_length(value) == expected_result);
      test_collatz_sequence_length(current_case + 1);
    }
}

void		test_collatz_max_sequence_starter(t_collatz_test_case *current_case)
{
  char		*name;
  long long	value;
  long long	expected_result;

  name = current_case->name;
  if (name != NULL)
    {
      puts(name);
      value = current_case->value;
      expected_result = current_case->expected_result;
      assert(collatz_max_sequence_starter(value, value) == expected_result);
      test_collatz_max_sequence_starter(current_case + 1);
    }
}

int		main()
{
  test_init_memo();
  test_collatz(collatz_cases);
  test_collatz_sequence_length(collatz_sequence_length_cases);
  test_collatz_max_sequence_starter(collatz_max_sequence_starter_cases);
  printf("{%lld}\n", collatz_max_sequence_starter(1000000, 1000000));
  return (0);
}
