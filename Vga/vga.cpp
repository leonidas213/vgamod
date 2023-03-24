#include "vga.h"
void vga::rgbStart(uint8_t hsync, uint8_t vsync, uint8_t redPin, uint8_t *buf)
{
    if (buf != nullptr)
    {
        this->address_pointer = (char *)&buf[0];
    }
    else
    {
    }

    uint hsync_offset = pio_add_program(pio0, &hsync_program);
    uint vsync_offset = pio_add_program(pio0, &vsync_program);
    uint rgb_offset = pio_add_program(pio0, &rgb_program);

    hsync_program_init(pio0, 0, hsync_offset, hsync);
    vsync_program_init(pio0, 1, vsync_offset, vsync);
    rgb_program_init(pio0, 2, rgb_offset, redPin);
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    // ===========================-== DMA Data Channels =================================================
    /////////////////////////////////////////////////////////////////////////////////////////////////////

    // DMA channels - 0 sends color data, 1 reconfigures and restarts 0
    int rgb_chan_0 = 0;
    int rgb_chan_1 = 1;

    // Channel Zero (sends color data to PIO VGA machine)
    dma_channel_config c0 = dma_channel_get_default_config(rgb_chan_0); // default configs
    channel_config_set_transfer_data_size(&c0, DMA_SIZE_8);             // 8-bit txfers
    channel_config_set_read_increment(&c0, true);                       // yes read incrementing
    channel_config_set_write_increment(&c0, false);                     // no write incrementing
    channel_config_set_dreq(&c0, DREQ_PIO0_TX2);                        // DREQ_PIO0_TX2 pacing (FIFO)
    channel_config_set_chain_to(&c0, rgb_chan_1);                       // chain to other channel

    dma_channel_configure(
        rgb_chan_0,             // Channel to be configured
        &c0,                    // The configuration we just created
        &pio0->txf[2],          // write address (RGB PIO TX FIFO)
        &this->address_pointer, // The initial read address (pixel color array)
        RGB_TXCOUNT,            // Number of transfers; in this case each is 1 byte.
        false                   // Don't start immediately.
    );

    // Channel One (reconfigures the first channel)
    dma_channel_config c1 = dma_channel_get_default_config(rgb_chan_1); // default configs
    channel_config_set_transfer_data_size(&c1, DMA_SIZE_32);            // 32-bit txfers
    channel_config_set_read_increment(&c1, false);                      // no read incrementing
    channel_config_set_write_increment(&c1, false);                     // no write incrementing
    channel_config_set_chain_to(&c1, rgb_chan_0);                       // chain to other channel

    dma_channel_configure(
        rgb_chan_1,                        // Channel to be configured
        &c1,                               // The configuration we just created
        &dma_hw->ch[rgb_chan_0].read_addr, // Write address (channel 0 read address)
        &address_pointer,                  // Read address (POINTER TO AN ADDRESS)
        1,                                 // Number of transfers, in this case each is 4 byte
        false                              // Don't start immediately.
    );

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    pio_sm_put_blocking(pio0, 0, H_ACTIVE);
    pio_sm_put_blocking(pio0, 1, V_ACTIVE);
    pio_sm_put_blocking(pio0, 2, RGB_ACTIVE);
}
void vga::monoStart(uint8_t hsync, uint8_t vsync, uint8_t redPin, uint8_t *buf)
{
    if (buf != nullptr)
    {
        this->address_pointer = (char *)&buf[0];
    }
    else
    {
    }

    uint hsync_offset = pio_add_program(pio0, &hsync_program);
    uint vsync_offset = pio_add_program(pio0, &vsync_program);
    uint mono_offset = pio_add_program(pio0, &mono_program);

    hsync_program_init(pio0, 0, hsync_offset, hsync);
    vsync_program_init(pio0, 1, vsync_offset, vsync);
    rgb_program_init(pio0, 2, mono_offset, redPin);
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    // ===========================-== DMA Data Channels =================================================
    /////////////////////////////////////////////////////////////////////////////////////////////////////

    // DMA channels - 0 sends color data, 1 reconfigures and restarts 0
    int rgb_chan_0 = 0;
    int rgb_chan_1 = 1;

    // Channel Zero (sends color data to PIO VGA machine)
    dma_channel_config c0 = dma_channel_get_default_config(rgb_chan_0); // default configs
    channel_config_set_transfer_data_size(&c0, DMA_SIZE_8);             // 8-bit txfers
    channel_config_set_read_increment(&c0, true);                       // yes read incrementing
    channel_config_set_write_increment(&c0, false);                     // no write incrementing
    channel_config_set_dreq(&c0, DREQ_PIO0_TX2);                        // DREQ_PIO0_TX2 pacing (FIFO)
    channel_config_set_chain_to(&c0, rgb_chan_1);                       // chain to other channel

    dma_channel_configure(
        rgb_chan_0,             // Channel to be configured
        &c0,                    // The configuration we just created
        &pio0->txf[2],          // write address (RGB PIO TX FIFO)
        &this->address_pointer, // The initial read address (pixel color array)
        MONO_TXCOUNT,           // Number of transfers; in this case each is 1 byte.
        false                   // Don't start immediately.
    );

    // Channel One (reconfigures the first channel)
    dma_channel_config c1 = dma_channel_get_default_config(rgb_chan_1); // default configs
    channel_config_set_transfer_data_size(&c1, DMA_SIZE_32);            // 32-bit txfers
    channel_config_set_read_increment(&c1, false);                      // no read incrementing
    channel_config_set_write_increment(&c1, false);                     // no write incrementing
    channel_config_set_chain_to(&c1, rgb_chan_0);                       // chain to other channel

    dma_channel_configure(
        rgb_chan_1,                        // Channel to be configured
        &c1,                               // The configuration we just created
        &dma_hw->ch[rgb_chan_0].read_addr, // Write address (channel 0 read address)
        &address_pointer,                  // Read address (POINTER TO AN ADDRESS)
        1,                                 // Number of transfers, in this case each is 4 byte
        false                              // Don't start immediately.
    );

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    pio_sm_put_blocking(pio0, 0, H_ACTIVE);
    pio_sm_put_blocking(pio0, 1, V_ACTIVE);
    pio_sm_put_blocking(pio0, 2, 20);
}
vga::vga(uint8_t hsync, uint8_t vsync, uint8_t redPin, uint8_t *buf, bool rgb)
{
    this->rgb = rgb;
    if (rgb)
    {
        rgbStart(hsync, vsync, redPin, buf);
    }
    else
    {
        monoStart(hsync, vsync, redPin + 1, buf);
    }
}
void vga::start()
{ // Start the two pio machine IN SYNC
  // Note that the RGB state machine is running at full speed,
  // so synchronization doesn't matter for that one. But, we'll
  // start them all simultaneously anyway.

    pio_enable_sm_mask_in_sync(pio0, ((1u << 0) | (1u << 1) | (1u << 2)));

    // Start DMA channel 0. Once started, the contents of the pixel color array
    // will be continously DMA's to the PIO machines that are driving the screen.
    // To change the contents of the screen, we need only change the contents
    // of that array.
    dma_start_channel_mask((1u << 0));
}