#ifndef __DTP_LINK_H__
#define __DTP_LINK_H__

/*----------------------------------------------------------------------------*/
/* Include Header Files                                                       */
/*----------------------------------------------------------------------------*/
#include <stdint.h>

/*----------------------------------------------------------------------------*/
/* Define Macros                                                              */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Typedef                                                                    */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Declare Functions                                                          */
/*----------------------------------------------------------------------------*/

/**
 * @brief dtp_link_frame_to_packet
 * @param packet_bytes
 * @param frame_bytes
 * @param frame_size
 * @return always return packet size and that depend on frame data
 */
int32_t dtp_link_frame_to_packet(uint8_t *packet_bytes, const uint8_t *frame_bytes, int32_t frame_size);

/**
 * @brief dtp_link_packet_to_frame
 * @param frame_bytes
 * @param packet_bytes
 * @param packet_size
 * @return always return frame size and that depend on packet data
 */
int32_t dtp_link_packet_to_frame(uint8_t *frame_bytes, const uint8_t *packet_bytes, int32_t packet_size);

/*----------------------------------------------------------------------------*/
/* Declare External Variables/Functions                                       */
/*----------------------------------------------------------------------------*/

#endif /*__DTP_LINK_H__*/
