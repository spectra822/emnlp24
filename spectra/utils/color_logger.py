################################################################################
# Copyright IBM Corporation 2023
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License a#t˚†
#       http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
################################################################################

"""
Rich and colorful Logging functions
"""

import logging
from rich.logging import RichHandler

FORMAT = "%(message)s"
logging.basicConfig(
    level="INFO", format=FORMAT, datefmt="[%X]", handlers=[RichHandler(show_path=False)]
)


class RichLog:
    """Common Logger that uses Rich"""

    log = logging.getLogger("rich")
    # Supress Elasticsearch Logger
    elasticsearch_logger = logging.getLogger("elastic_transport.transport")
    elasticsearch_logger.setLevel(logging.CRITICAL)

    @staticmethod
    def info(msg: str):
        """Log level INFO"""
        RichLog.log.info(msg, extra={"markup": True})

    @staticmethod
    def warn(msg: str):
        """Log level WARNING"""
        RichLog.log.warning(msg, extra={"markup": True})

    @staticmethod
    def debug(msg: str):
        """Log level DEBUG"""
        RichLog.log.debug(msg, extra={"markup": True})

    @staticmethod
    def error(msg: str):
        """Log level ERROR"""
        RichLog.log.error(msg, extra={"markup": True})
