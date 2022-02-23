
#define CONCATENATE(x,y) x##y
#define EXPAND(x) x

#define FOR_EACH_01(Macro, x, ...) Macro(x)
#define FOR_EACH_02(Macro, x, ...) Macro(x), EXPAND(FOR_EACH_01(Macro, __VA_ARGS__))
#define FOR_EACH_03(Macro, x, ...) Macro(x), EXPAND(FOR_EACH_02(Macro, __VA_ARGS__))
#define FOR_EACH_04(Macro, x, ...) Macro(x), EXPAND(FOR_EACH_03(Macro, __VA_ARGS__))
#define FOR_EACH_05(Macro, x, ...) Macro(x), EXPAND(FOR_EACH_04(Macro, __VA_ARGS__))
#define FOR_EACH_06(Macro, x, ...) Macro(x), EXPAND(FOR_EACH_05(Macro, __VA_ARGS__))
#define FOR_EACH_07(Macro, x, ...) Macro(x), EXPAND(FOR_EACH_06(Macro, __VA_ARGS__))
#define FOR_EACH_08(Macro, x, ...) Macro(x), EXPAND(FOR_EACH_07(Macro, __VA_ARGS__))
#define FOR_EACH_09(Macro, x, ...) Macro(x), EXPAND(FOR_EACH_08(Macro, __VA_ARGS__))
#define FOR_EACH_10(Macro, x, ...) Macro(x), EXPAND(FOR_EACH_09(Macro, __VA_ARGS__))
#define FOR_EACH_11(Macro, x, ...) Macro(x), EXPAND(FOR_EACH_10(Macro, __VA_ARGS__))
#define FOR_EACH_12(Macro, x, ...) Macro(x), EXPAND(FOR_EACH_11(Macro, __VA_ARGS__))
#define FOR_EACH_13(Macro, x, ...) Macro(x), EXPAND(FOR_EACH_12(Macro, __VA_ARGS__))
#define FOR_EACH_14(Macro, x, ...) Macro(x), EXPAND(FOR_EACH_13(Macro, __VA_ARGS__))
#define FOR_EACH_15(Macro, x, ...) Macro(x), EXPAND(FOR_EACH_14(Macro, __VA_ARGS__))
#define FOR_EACH_16(Macro, x, ...) Macro(x), EXPAND(FOR_EACH_15(Macro, __VA_ARGS__))

#define VA_LENGTH_(_16, _15, _14, _13, _12, _11, _10, _09, _08, _07, _06, _05, _04, _03, _02, _01, N, ...) N
#define VA_LENGTH(...) EXPAND(VA_LENGTH_(__VA_ARGS__, 16, 15, 14, 13, 12, 11, 10, 09, 08, 07, 06, 05, 04, 03, 02, 01, 00))

#define FOR_EACH_(N, Macro, ...) EXPAND(CONCATENATE(FOR_EACH_, N)(Macro, __VA_ARGS__))
#define FOR_EACH(Macro, ...) FOR_EACH_(VA_LENGTH(__VA_ARGS__), Macro, __VA_ARGS__)