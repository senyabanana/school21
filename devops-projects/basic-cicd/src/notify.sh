#!/bin/bash

TELEGRAM_BOT_TOKEN=6848787578:AAE1JfA72P-6a2qZ9GAfrzwLi9JmGTyMqqc
TELEGRAM_USER_ID=415282459
URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"
TEXT="Чел, хорош!%0A Project:+$CI_PROJECT_NAME%0A$CI_JOB_NAME+$CI_JOB_STATUS"

curl -s -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null