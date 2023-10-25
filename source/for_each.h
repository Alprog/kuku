
#define CONCATENATE(x,y,z) x##y##z
#define EXPAND(x) x

#define VA_LENGTH_(_16, _15, _14, _13, _12, _11, _10, _09, _08, _07, _06, _05, _04, _03, _02, _01, N, ...) N
#define VA_LENGTH(...) EXPAND(VA_LENGTH_(__VA_ARGS__, 16, 15, 14, 13, 12, 11, 10, 09, 08, 07, 06, 05, 04, 03, 02, 01, 00))

#define FOR_00(Macro, x, ...)
#define FOR_01(Macro, x, ...) Macro(x)
#define FOR_02(Macro, x, ...) Macro(x), EXPAND(FOR_01(Macro, __VA_ARGS__))
#define FOR_03(Macro, x, ...) Macro(x), EXPAND(FOR_02(Macro, __VA_ARGS__))
#define FOR_04(Macro, x, ...) Macro(x), EXPAND(FOR_03(Macro, __VA_ARGS__))
#define FOR_05(Macro, x, ...) Macro(x), EXPAND(FOR_04(Macro, __VA_ARGS__))
#define FOR_06(Macro, x, ...) Macro(x), EXPAND(FOR_05(Macro, __VA_ARGS__))
#define FOR_07(Macro, x, ...) Macro(x), EXPAND(FOR_06(Macro, __VA_ARGS__))
#define FOR_08(Macro, x, ...) Macro(x), EXPAND(FOR_07(Macro, __VA_ARGS__))
#define FOR_09(Macro, x, ...) Macro(x), EXPAND(FOR_08(Macro, __VA_ARGS__))
#define FOR_10(Macro, x, ...) Macro(x), EXPAND(FOR_09(Macro, __VA_ARGS__))
#define FOR_11(Macro, x, ...) Macro(x), EXPAND(FOR_10(Macro, __VA_ARGS__))
#define FOR_12(Macro, x, ...) Macro(x), EXPAND(FOR_11(Macro, __VA_ARGS__))
#define FOR_13(Macro, x, ...) Macro(x), EXPAND(FOR_12(Macro, __VA_ARGS__))
#define FOR_14(Macro, x, ...) Macro(x), EXPAND(FOR_13(Macro, __VA_ARGS__))
#define FOR_15(Macro, x, ...) Macro(x), EXPAND(FOR_14(Macro, __VA_ARGS__))
#define FOR_16(Macro, x, ...) Macro(x), EXPAND(FOR_15(Macro, __VA_ARGS__))

#define FOR_(N, Macro, ...) EXPAND(CONCATENATE(FOR_, N)(Macro, __VA_ARGS__))
#define FOR_EACH(Macro, ...) FOR_(VA_LENGTH(__VA_ARGS__), Macro, __VA_ARGS__)

#define FOR_SEPARATOR_00(Macro, Separator, x, ...)
#define FOR_SEPARATOR_01(Macro, Separator, x, ...) Macro(x)
#define FOR_SEPARATOR_02(Macro, Separator, x, ...) Macro(x)Separator EXPAND(FOR_SEPARATOR_01(Macro, Separator, __VA_ARGS__))
#define FOR_SEPARATOR_03(Macro, Separator, x, ...) Macro(x)Separator EXPAND(FOR_SEPARATOR_02(Macro, Separator, __VA_ARGS__))
#define FOR_SEPARATOR_04(Macro, Separator, x, ...) Macro(x)Separator EXPAND(FOR_SEPARATOR_03(Macro, Separator, __VA_ARGS__))
#define FOR_SEPARATOR_05(Macro, Separator, x, ...) Macro(x)Separator EXPAND(FOR_SEPARATOR_04(Macro, Separator, __VA_ARGS__))
#define FOR_SEPARATOR_06(Macro, Separator, x, ...) Macro(x)Separator EXPAND(FOR_SEPARATOR_05(Macro, Separator, __VA_ARGS__))
#define FOR_SEPARATOR_07(Macro, Separator, x, ...) Macro(x)Separator EXPAND(FOR_SEPARATOR_06(Macro, Separator, __VA_ARGS__))
#define FOR_SEPARATOR_08(Macro, Separator, x, ...) Macro(x)Separator EXPAND(FOR_SEPARATOR_07(Macro, Separator, __VA_ARGS__))
#define FOR_SEPARATOR_09(Macro, Separator, x, ...) Macro(x)Separator EXPAND(FOR_SEPARATOR_08(Macro, Separator, __VA_ARGS__))
#define FOR_SEPARATOR_10(Macro, Separator, x, ...) Macro(x)Separator EXPAND(FOR_SEPARATOR_09(Macro, Separator, __VA_ARGS__))
#define FOR_SEPARATOR_11(Macro, Separator, x, ...) Macro(x)Separator EXPAND(FOR_SEPARATOR_10(Macro, Separator, __VA_ARGS__))
#define FOR_SEPARATOR_12(Macro, Separator, x, ...) Macro(x)Separator EXPAND(FOR_SEPARATOR_11(Macro, Separator, __VA_ARGS__))
#define FOR_SEPARATOR_13(Macro, Separator, x, ...) Macro(x)Separator EXPAND(FOR_SEPARATOR_12(Macro, Separator, __VA_ARGS__))
#define FOR_SEPARATOR_14(Macro, Separator, x, ...) Macro(x)Separator EXPAND(FOR_SEPARATOR_13(Macro, Separator, __VA_ARGS__))
#define FOR_SEPARATOR_15(Macro, Separator, x, ...) Macro(x)Separator EXPAND(FOR_SEPARATOR_14(Macro, Separator, __VA_ARGS__))
#define FOR_SEPARATOR_16(Macro, Separator, x, ...) Macro(x)Separator EXPAND(FOR_SEPARATOR_15(Macro, Separator, __VA_ARGS__))

#define FOR_SEPARATOR_(N, Macro, Separator, ...) EXPAND(CONCATENATE(FOR_SEPARATOR_, N)(Macro, Separator, __VA_ARGS__))
#define FOR_EACH_SEPARATOR(Macro, Separator, ...) FOR_SEPARATOR_(VA_LENGTH(__VA_ARGS__), Macro, Separator, __VA_ARGS__)

#define VALUE_01_MINUS_01 00
#define VALUE_02_MINUS_01 01
#define VALUE_03_MINUS_01 02
#define VALUE_04_MINUS_01 03
#define VALUE_05_MINUS_01 04
#define VALUE_06_MINUS_01 05
#define VALUE_07_MINUS_01 06
#define VALUE_08_MINUS_01 07
#define VALUE_09_MINUS_01 08
#define VALUE_10_MINUS_01 09
#define VALUE_11_MINUS_01 10
#define VALUE_12_MINUS_01 11
#define VALUE_13_MINUS_01 12
#define VALUE_14_MINUS_01 13
#define VALUE_15_MINUS_01 14
#define VALUE_16_MINUS_01 15

#define MINUS(N) EXPAND(CONCATENATE(VALUE_, N, _MINUS_01))

