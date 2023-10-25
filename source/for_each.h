
#define CONCATENATE(x,y) x##y
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

#define MINUS_01 00
#define MINUS_02 01
#define MINUS_03 02
#define MINUS_04 03
#define MINUS_05 04
#define MINUS_06 05
#define MINUS_07 06
#define MINUS_08 07
#define MINUS_09 08
#define MINUS_10 09
#define MINUS_11 10
#define MINUS_12 11
#define MINUS_13 12
#define MINUS_14 13
#define MINUS_15 14
#define MINUS_16 15

#define MINUS(N) EXPAND(CONCATENATE(MINUS_, N))

