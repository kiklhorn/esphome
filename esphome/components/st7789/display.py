import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import display, spi
from esphome.const import (
    CONF_COLOR_PALETTE,
    CONF_DC_PIN,
    CONF_ID,
    CONF_LAMBDA,
    CONF_MODEL,
    CONF_PAGES,
    CONF_RAW_DATA_ID,
    CONF_RESET_PIN,
)
from esphome.core import HexInt

DEPENDENCIES = ["spi"]

CONF_LED_PIN = "led_pin"

st7789_ns = cg.esphome_ns.namespace("st7789")
st7789 = st7789_ns.class_(
    "ST7789Display", cg.PollingComponent, spi.SPIDevice, display.DisplayBuffer
)
ST7789M5Stack = st7789_ns.class_("ST7789M5Stack", st7789)
ST7789TFT24 = st7789_ns.class_("ST7789TFT24", st7789)
ST7789TFT24R = st7789_ns.class_("ST7789TFT24R", st7789)
ST7789TFT13R = st7789_ns.class_("ST7789TFT13R", st7789)

ST7789Model = st7789_ns.enum("ST7789Model")
ST7789ColorMode = st7789_ns.enum("ST7789ColorMode")

MODELS = {
    "M5STACK": ST7789Model.M5STACK,
    "TFT_2.4": ST7789Model.TFT_24,
    "TFT_2.4R": ST7789Model.TFT_24R,
    "TFT_1.3R": ST7789Model.TFT_13R,
}

ST7789_MODEL = cv.enum(MODELS, upper=True, space="_")

COLOR_PALETTE = cv.one_of("NONE", "GRAYSCALE")

CONFIG_SCHEMA = cv.All(
    display.FULL_DISPLAY_SCHEMA.extend(
        {
            cv.GenerateID(): cv.declare_id(st7789),
            cv.Required(CONF_MODEL): ST7789_MODEL,
            cv.Required(CONF_DC_PIN): pins.gpio_output_pin_schema,
            cv.Optional(CONF_RESET_PIN): pins.gpio_output_pin_schema,
            cv.Optional(CONF_LED_PIN): pins.gpio_output_pin_schema,
            cv.Optional(CONF_COLOR_PALETTE, default="NONE"): COLOR_PALETTE,
            cv.GenerateID(CONF_RAW_DATA_ID): cv.declare_id(cg.uint8),
        }
    )
    .extend(cv.polling_component_schema("1s"))
    .extend(spi.spi_device_schema(False)),
    cv.has_at_most_one_key(CONF_PAGES, CONF_LAMBDA),
)


async def to_code(config):
    if config[CONF_MODEL] == "M5STACK":
        lcd_type = ST7789M5Stack
    if config[CONF_MODEL] == "TFT_2.4":
        lcd_type = ST7789TFT24
    if config[CONF_MODEL] == "TFT_2.4R":
        lcd_type = ST7789TFT24R
    if config[CONF_MODEL] == "TFT_1.3R":
        lcd_type = ST7789TFT13R
    rhs = lcd_type.new()
    var = cg.Pvariable(config[CONF_ID], rhs)

    await cg.register_component(var, config)
    await display.register_display(var, config)
    await spi.register_spi_device(var, config)
    cg.add(var.set_model(config[CONF_MODEL]))
    dc = await cg.gpio_pin_expression(config[CONF_DC_PIN])
    cg.add(var.set_dc_pin(dc))

    if CONF_LAMBDA in config:
        lambda_ = await cg.process_lambda(
            config[CONF_LAMBDA], [(display.DisplayBufferRef, "it")], return_type=cg.void
        )
        cg.add(var.set_writer(lambda_))
    if CONF_RESET_PIN in config:
        reset = await cg.gpio_pin_expression(config[CONF_RESET_PIN])
        cg.add(var.set_reset_pin(reset))
    if CONF_LED_PIN in config:
        led_pin = await cg.gpio_pin_expression(config[CONF_LED_PIN])
        cg.add(var.set_led_pin(led_pin))

    if config[CONF_COLOR_PALETTE] == "GRAYSCALE":
        cg.add(var.set_buffer_color_mode(ST7789ColorMode.BITS_8_INDEXED))
        rhs = []
        for x in range(256):
            rhs.extend([HexInt(x), HexInt(x), HexInt(x)])
        prog_arr = cg.progmem_array(config[CONF_RAW_DATA_ID], rhs)
        cg.add(var.set_palette(prog_arr))
    else:
        pass