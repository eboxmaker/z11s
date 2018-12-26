#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "utils/log.h"
int
socket_set_keepalive (int fd)
{
  int ret, error, flag, alive, idle, cnt, intv;

  /* Set: use keepalive on fd */
  alive = 1;
  if (setsockopt
      (fd, SOL_SOCKET, SO_KEEPALIVE, &alive,
       sizeof alive) != 0)
    {
      LOGE ("Set keepalive error: %s.\n", strerror (errno));
      return -1;
    }
  else
  {
      LOGE ("Set keepalive : %d\n", alive);
  }

  /* １０秒钟无数据，触发保活机制，发送保活包 */
  idle = 60;
  if (setsockopt (fd, SOL_TCP, TCP_KEEPIDLE, &idle, sizeof idle) != 0)
    {
	  LOGE("Set keepalive idle error: %s.\n", strerror (errno));
      return -1;
    }
  else
  {
      LOGE ("Set keepalive idle: %d.\n", idle);
  }
  /* 如果没有收到回应，则５秒钟后重发保活包 */
  intv = 5;
  if (setsockopt (fd, SOL_TCP, TCP_KEEPINTVL, &intv, sizeof intv) != 0)
    {
	  LOGE("Set keepalive intv error: %s.\n", strerror (errno));
      return -1;
    }
  else
  {
      LOGE ("Set keepalive intv: %d.\n", intv);
  }
  /* 连续３次没收到保活包，视为连接失效 */
  cnt = 3;
  if (setsockopt (fd, SOL_TCP, TCP_KEEPCNT, &cnt, sizeof cnt) != 0)
    {
	  LOGE("Set keepalive cnt error: %s.\n", strerror (errno));
      return -1;
    }
  else
  {
      LOGE ("Set keepalive cnt: %d.\n", cnt);
  }
  return 0;
}
