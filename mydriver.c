// SPDX-License-Identifier: GPL-2.0-only
/*
 * mydriver.c -- Minimal MYDRIVER ALSA SoC Codec driver for MAX98357A-type DACs
 */

#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <sound/pcm.h>
#include <sound/soc.h>
#include <sound/soc-dai.h>

static const struct snd_soc_component_driver mydriver_component_driver = {
	.idle_bias_on      = 1,
	.use_pmdown_time   = 1,
	.endianness        = 1,
};

static struct snd_soc_dai_driver mydriver_dai_driver = {
	.name = "HiFi",
	.playback = {
		.stream_name   = "HiFi Playback",
		.formats       = SNDRV_PCM_FMTBIT_S16 |
		                 SNDRV_PCM_FMTBIT_S24 |
		                 SNDRV_PCM_FMTBIT_S32,
		.rates         = SNDRV_PCM_RATE_8000 |
		                 SNDRV_PCM_RATE_16000 |
		                 SNDRV_PCM_RATE_32000 |
		                 SNDRV_PCM_RATE_44100 |
		                 SNDRV_PCM_RATE_48000 |
		                 SNDRV_PCM_RATE_88200 |
		                 SNDRV_PCM_RATE_96000,
		.rate_min      = 8000,
		.rate_max      = 96000,
		.channels_min  = 1,
		.channels_max  = 2,
	},
};

static int mydriver_platform_probe(struct platform_device *pdev)
{
	return devm_snd_soc_register_component(&pdev->dev,
	                                       &mydriver_component_driver,
	                                       &mydriver_dai_driver,
	                                       1);
}

static const struct of_device_id mydriver_device_id[] = {
	{ .compatible = "maxim,mydriver" },
	{}
};
MODULE_DEVICE_TABLE(of, mydriver_device_id);

static struct platform_driver mydriver_platform_driver = {
	.driver = {
		.name = "mydriver",
		.of_match_table = mydriver_device_id,
	},
	.probe = mydriver_platform_probe,
};
module_platform_driver(mydriver_platform_driver);

MODULE_DESCRIPTION("Minimal MYDRIVER Codec Driver");
MODULE_AUTHOR("yunji965@gmail.com");
MODULE_LICENSE("GPL v2");
