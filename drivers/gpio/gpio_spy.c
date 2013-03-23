/*
 * gpio_spy.c
 *
 *  Created on: 11.03.2013
 *      Author: erwin
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/printk.h>
#include <asm/gpio.h>

int dumpPins(struct gpio_chip *chip, void *data)
{
  int i;
  static struct gpio_chip *currChip;
  const char *res;
  // if this is a new chip / segment
  if(chip != currChip)
  {
    currChip = chip;
    // dump all pins of chip
    for(i=0; i<chip->ngpio; i++ )
    {
      // get reservation string
      res = gpiochip_is_requested(chip, i);
      // dump reservation
      printk("%d : %s\n",
             chip->base+i,
             res ? res : "");
    }
  }
  return 0;
}

static int __init init_gpio_spy(void)
{
  gpiochip_find(NULL, dumpPins);
  return 0;
}

static void __exit exit_gpio_spy(void)
{
}

module_init(init_gpio_spy);
module_exit(exit_gpio_spy);

/* Module information */
MODULE_AUTHOR("fr3ts0n");
MODULE_DESCRIPTION("GPIO spy module");
MODULE_LICENSE("GPL");

