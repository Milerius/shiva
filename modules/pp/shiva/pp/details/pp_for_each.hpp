//
// Created by doom on 03/10/17.
//

#ifndef CORE_PP_DETAILS_FOR_EACH_HPP
#define CORE_PP_DETAILS_FOR_EACH_HPP

#define __FOR_EACH_EXPAND(x)    x

#define __FOR_EACH1(fct, cur, ...)                                          \
    fct(cur)

#define __FOR_EACH2(fct, cur, ...)                                          \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH1(fct, __VA_ARGS__))

#define __FOR_EACH3(fct, cur, ...)                                          \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH2(fct, __VA_ARGS__))

#define __FOR_EACH4(fct, cur, ...)                                          \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH3(fct, __VA_ARGS__))

#define __FOR_EACH5(fct, cur, ...)                                          \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH4(fct, __VA_ARGS__))

#define __FOR_EACH6(fct, cur, ...)                                          \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH5(fct, __VA_ARGS__))

#define __FOR_EACH7(fct, cur, ...)                                          \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH6(fct, __VA_ARGS__))

#define __FOR_EACH8(fct, cur, ...)                                          \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH7(fct, __VA_ARGS__))

#define __FOR_EACH9(fct, cur, ...)                                          \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH8(fct, __VA_ARGS__))

#define __FOR_EACH10(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH9(fct, __VA_ARGS__))

#define __FOR_EACH11(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH10(fct, __VA_ARGS__))

#define __FOR_EACH12(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH11(fct, __VA_ARGS__))

#define __FOR_EACH13(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH12(fct, __VA_ARGS__))

#define __FOR_EACH14(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH13(fct, __VA_ARGS__))

#define __FOR_EACH15(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH14(fct, __VA_ARGS__))

#define __FOR_EACH16(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH15(fct, __VA_ARGS__))

#define __FOR_EACH17(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH16(fct, __VA_ARGS__))

#define __FOR_EACH18(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH17(fct, __VA_ARGS__))

#define __FOR_EACH19(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH18(fct, __VA_ARGS__))

#define __FOR_EACH20(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH19(fct, __VA_ARGS__))

#define __FOR_EACH21(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH20(fct, __VA_ARGS__))

#define __FOR_EACH22(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH21(fct, __VA_ARGS__))

#define __FOR_EACH23(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH22(fct, __VA_ARGS__))

#define __FOR_EACH24(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH23(fct, __VA_ARGS__))

#define __FOR_EACH25(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH24(fct, __VA_ARGS__))

#define __FOR_EACH26(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH25(fct, __VA_ARGS__))

#define __FOR_EACH27(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH26(fct, __VA_ARGS__))

#define __FOR_EACH28(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH27(fct, __VA_ARGS__))

#define __FOR_EACH29(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH28(fct, __VA_ARGS__))

#define __FOR_EACH30(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH29(fct, __VA_ARGS__))

#define __FOR_EACH31(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH30(fct, __VA_ARGS__))

#define __FOR_EACH32(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH31(fct, __VA_ARGS__))

#define __FOR_EACH33(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH32(fct, __VA_ARGS__))

#define __FOR_EACH34(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH33(fct, __VA_ARGS__))

#define __FOR_EACH35(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH34(fct, __VA_ARGS__))

#define __FOR_EACH36(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH35(fct, __VA_ARGS__))

#define __FOR_EACH37(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH36(fct, __VA_ARGS__))

#define __FOR_EACH38(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH37(fct, __VA_ARGS__))

#define __FOR_EACH39(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH38(fct, __VA_ARGS__))

#define __FOR_EACH40(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH39(fct, __VA_ARGS__))

#define __FOR_EACH41(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH40(fct, __VA_ARGS__))

#define __FOR_EACH42(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH41(fct, __VA_ARGS__))

#define __FOR_EACH43(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH42(fct, __VA_ARGS__))

#define __FOR_EACH44(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH43(fct, __VA_ARGS__))

#define __FOR_EACH45(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH44(fct, __VA_ARGS__))

#define __FOR_EACH46(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH45(fct, __VA_ARGS__))

#define __FOR_EACH47(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH46(fct, __VA_ARGS__))

#define __FOR_EACH48(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH47(fct, __VA_ARGS__))

#define __FOR_EACH49(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH48(fct, __VA_ARGS__))

#define __FOR_EACH50(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH49(fct, __VA_ARGS__))

#define __FOR_EACH51(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH50(fct, __VA_ARGS__))

#define __FOR_EACH52(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH51(fct, __VA_ARGS__))

#define __FOR_EACH53(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH52(fct, __VA_ARGS__))

#define __FOR_EACH54(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH53(fct, __VA_ARGS__))

#define __FOR_EACH55(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH54(fct, __VA_ARGS__))

#define __FOR_EACH56(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH55(fct, __VA_ARGS__))

#define __FOR_EACH57(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH56(fct, __VA_ARGS__))

#define __FOR_EACH58(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH57(fct, __VA_ARGS__))

#define __FOR_EACH59(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH58(fct, __VA_ARGS__))

#define __FOR_EACH60(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH59(fct, __VA_ARGS__))

#define __FOR_EACH61(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH60(fct, __VA_ARGS__))

#define __FOR_EACH62(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH61(fct, __VA_ARGS__))

#define __FOR_EACH63(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH62(fct, __VA_ARGS__))

#define __FOR_EACH64(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH63(fct, __VA_ARGS__))

#define __FOR_EACH65(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH64(fct, __VA_ARGS__))

#define __FOR_EACH66(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH65(fct, __VA_ARGS__))

#define __FOR_EACH67(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH66(fct, __VA_ARGS__))

#define __FOR_EACH68(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH67(fct, __VA_ARGS__))

#define __FOR_EACH69(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH68(fct, __VA_ARGS__))

#define __FOR_EACH70(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH69(fct, __VA_ARGS__))

#define __FOR_EACH71(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH70(fct, __VA_ARGS__))

#define __FOR_EACH72(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH71(fct, __VA_ARGS__))

#define __FOR_EACH73(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH72(fct, __VA_ARGS__))

#define __FOR_EACH74(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH73(fct, __VA_ARGS__))

#define __FOR_EACH75(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH74(fct, __VA_ARGS__))

#define __FOR_EACH76(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH75(fct, __VA_ARGS__))

#define __FOR_EACH77(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH76(fct, __VA_ARGS__))

#define __FOR_EACH78(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH77(fct, __VA_ARGS__))

#define __FOR_EACH79(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH78(fct, __VA_ARGS__))

#define __FOR_EACH80(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH79(fct, __VA_ARGS__))

#define __FOR_EACH81(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH80(fct, __VA_ARGS__))

#define __FOR_EACH82(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH81(fct, __VA_ARGS__))

#define __FOR_EACH83(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH82(fct, __VA_ARGS__))

#define __FOR_EACH84(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH83(fct, __VA_ARGS__))

#define __FOR_EACH85(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH84(fct, __VA_ARGS__))

#define __FOR_EACH86(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH85(fct, __VA_ARGS__))

#define __FOR_EACH87(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH86(fct, __VA_ARGS__))

#define __FOR_EACH88(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH87(fct, __VA_ARGS__))

#define __FOR_EACH89(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH88(fct, __VA_ARGS__))

#define __FOR_EACH90(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH89(fct, __VA_ARGS__))

#define __FOR_EACH91(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH90(fct, __VA_ARGS__))

#define __FOR_EACH92(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH91(fct, __VA_ARGS__))

#define __FOR_EACH93(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH92(fct, __VA_ARGS__))

#define __FOR_EACH94(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH93(fct, __VA_ARGS__))

#define __FOR_EACH95(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH94(fct, __VA_ARGS__))

#define __FOR_EACH96(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH95(fct, __VA_ARGS__))

#define __FOR_EACH97(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH96(fct, __VA_ARGS__))

#define __FOR_EACH98(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH97(fct, __VA_ARGS__))

#define __FOR_EACH99(fct, cur, ...)                                         \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH98(fct, __VA_ARGS__))

#define __FOR_EACH100(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH99(fct, __VA_ARGS__))

#define __FOR_EACH101(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH100(fct, __VA_ARGS__))

#define __FOR_EACH102(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH101(fct, __VA_ARGS__))

#define __FOR_EACH103(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH102(fct, __VA_ARGS__))

#define __FOR_EACH104(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH103(fct, __VA_ARGS__))

#define __FOR_EACH105(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH104(fct, __VA_ARGS__))

#define __FOR_EACH106(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH105(fct, __VA_ARGS__))

#define __FOR_EACH107(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH106(fct, __VA_ARGS__))

#define __FOR_EACH108(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH107(fct, __VA_ARGS__))

#define __FOR_EACH109(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH108(fct, __VA_ARGS__))

#define __FOR_EACH110(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH109(fct, __VA_ARGS__))

#define __FOR_EACH111(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH110(fct, __VA_ARGS__))

#define __FOR_EACH112(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH111(fct, __VA_ARGS__))

#define __FOR_EACH113(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH112(fct, __VA_ARGS__))

#define __FOR_EACH114(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH113(fct, __VA_ARGS__))

#define __FOR_EACH115(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH114(fct, __VA_ARGS__))

#define __FOR_EACH116(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH115(fct, __VA_ARGS__))

#define __FOR_EACH117(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH116(fct, __VA_ARGS__))

#define __FOR_EACH118(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH117(fct, __VA_ARGS__))

#define __FOR_EACH119(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH118(fct, __VA_ARGS__))

#define __FOR_EACH120(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH119(fct, __VA_ARGS__))

#define __FOR_EACH121(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH120(fct, __VA_ARGS__))

#define __FOR_EACH122(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH121(fct, __VA_ARGS__))

#define __FOR_EACH123(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH122(fct, __VA_ARGS__))

#define __FOR_EACH124(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH123(fct, __VA_ARGS__))

#define __FOR_EACH125(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH124(fct, __VA_ARGS__))

#define __FOR_EACH126(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH125(fct, __VA_ARGS__))

#define __FOR_EACH127(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH126(fct, __VA_ARGS__))

#define __FOR_EACH128(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH127(fct, __VA_ARGS__))

#define __FOR_EACH129(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH128(fct, __VA_ARGS__))

#define __FOR_EACH130(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH129(fct, __VA_ARGS__))

#define __FOR_EACH131(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH130(fct, __VA_ARGS__))

#define __FOR_EACH132(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH131(fct, __VA_ARGS__))

#define __FOR_EACH133(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH132(fct, __VA_ARGS__))

#define __FOR_EACH134(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH133(fct, __VA_ARGS__))

#define __FOR_EACH135(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH134(fct, __VA_ARGS__))

#define __FOR_EACH136(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH135(fct, __VA_ARGS__))

#define __FOR_EACH137(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH136(fct, __VA_ARGS__))

#define __FOR_EACH138(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH137(fct, __VA_ARGS__))

#define __FOR_EACH139(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH138(fct, __VA_ARGS__))

#define __FOR_EACH140(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH139(fct, __VA_ARGS__))

#define __FOR_EACH141(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH140(fct, __VA_ARGS__))

#define __FOR_EACH142(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH141(fct, __VA_ARGS__))

#define __FOR_EACH143(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH142(fct, __VA_ARGS__))

#define __FOR_EACH144(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH143(fct, __VA_ARGS__))

#define __FOR_EACH145(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH144(fct, __VA_ARGS__))

#define __FOR_EACH146(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH145(fct, __VA_ARGS__))

#define __FOR_EACH147(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH146(fct, __VA_ARGS__))

#define __FOR_EACH148(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH147(fct, __VA_ARGS__))

#define __FOR_EACH149(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH148(fct, __VA_ARGS__))

#define __FOR_EACH150(fct, cur, ...)                                        \
    fct(cur)                                                                \
    __FOR_EACH_EXPAND(__FOR_EACH149(fct, __VA_ARGS__))

#endif //CORE_PP_DETAILS_FOR_EACH_HPP
