#include "defines.h"
#include "interrupt.h"
#include "kozos.h"
#include "lib.h"

/* システムタスクとユーザスレッドの起動 */
static int start_threads(int argc, char *argv[]) {
  kz_run(test11_1_main, "test_11_1", 1, 0x100, 0, NULL);
  kz_run(test11_2_main, "test_11_2", 2, 0x100, 0, NULL);

  kz_chpri(15); /* 優先順位を下げてアイドルスレッドに移行する */
  INTR_ENABLE;
  while (1) {
    asm volatile("sleep"); /* 省電力モードに移行 */
  }

  return 0;
}

int main(void) {
  INTR_DISABLE; /* 割り込み無効にする */

  puts("kozos boot succeed!\n");

  /* OSの動作開始 */
  kz_start(start_threads, "idle", 0, 0x100, 0, NULL);
  /* ここには戻ってこない */

  return 0;
}
