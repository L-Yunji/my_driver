# MYDRIVER: Minimal ALSA SoC Codec Driver for MAX98357A

## 개요

이 드라이버는 **MAX98357A** 및 유사한 I2S DAC 장치용으로 설계된 **경량화 ALSA SoC Codec 드라이버**입니다. 복잡한 기능 없이 단순한 **오디오 출력만 필요한 경우**를 위해 최소한의 구성으로 작동하며, 저전력 시스템이나 커스텀 보드에 적합합니다.

## 주요 특징

| 항목     | 설명                             |
| ------ | ------------------------------ |
| 플랫폼    | Raspberry Pi        |
| 인터페이스  | I2S                            |
| 오디오 기능 | Playback only                  |
| 채널     | Mono(1) \~ Stereo(2)           |
| 샘플레이트  | 8kHz \~ 96kHz                  |
| 포맷     | S16\_LE, S24\_LE, S32\_LE      |
| 경량화 요소 | DAPM, mute GPIO, SD\_MODE 등 생략 |

## 드라이버 구조 요약

* `snd_soc_component_driver`로 기본 컴포넌트 등록
* `snd_soc_dai_driver`로 DAI (Digital Audio Interface) 정의
* `platform_driver`는 `"maxim,mydriver"`로 device tree 매칭
* Device Tree 오버레이를 통해 `simple-audio-card`와 연결

---

## 오버레이 컴파일 및 적용 방법

### 1. `.dts` 파일 컴파일

```bash
dtc -@ -I dts -O dtb -o mydriver.dtbo mydriver-overlay.dts
```

### 2. Raspberry Pi 오버레이 디렉토리에 복사

```bash
sudo cp mydriver.dtbo /boot/overlays/
```

### 3. `config.txt`에 오버레이 등록

```ini
# /boot/config.txt
dtoverlay=mydriver
```

### 4. I2S 인터페이스 활성화 (필요 시)

```ini
dtparam=i2s=on
```

---

## 드라이버 빌드 및 로드

```bash
# 컴파일
make

# 드라이버 삽입
sudo insmod mydriver.ko

# dmesg 확인
dmesg | grep mydriver
```

---

## aplay 테스트

```bash
aplay -D plughw:0,0 test.wav
```

> `aplay -l`로 장치 목록을 확인하세요. MYDRIVER가 잡혀 있어야 합니다.

<img width="643" height="344" alt="image (6)" src="https://github.com/user-attachments/assets/420dad80-28a8-49a1-be41-e617fd8ab5d2" />


## 참고 사항

* `MAX98357A`는 레지스터 설정 없이 I2S 신호만 받으면 작동하는 DAC입니다.
* 이 드라이버는 **컨트롤 인터페이스가 없으며**, mute나 power 제어도 제공하지 않습니다.
* **복잡한 오디오 파이프라인이 필요 없는 경우** 이상적입니다.

---
