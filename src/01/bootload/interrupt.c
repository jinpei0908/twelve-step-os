#include "interrupt.h"
#include "defines.h"
#include "intr.h"

/* ソフトウェア割り込みベクタの初期化 */
int softvec_init(void) {
  int type;
  for (type = 0; type < SOFTVEC_TYPE_NUM; type++) {
    softvec_setintr(type, NULL);
  }
  return 0;
}

/* ソフトウェア割り込みベクタの設定 */
int softvec_setintr(softvec_type_t type, softvec_handler_t handler) {
  SOFTVECS[type] = handler;
  return 0;
}

/*
 * 共通割り込みハンドラ
 * ソフトウェア割り込みベクタを見て各ハンドラに分岐する
 */
void interrupt(softvec_type_t type, unsigned long sp) {
  softvec_handler_t handler = SOFTVECS[type];
  if (handler) {
    handler(type, sp);
  }
}
