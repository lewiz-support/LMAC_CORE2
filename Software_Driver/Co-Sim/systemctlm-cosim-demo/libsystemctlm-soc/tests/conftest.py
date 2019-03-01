import pytest
import sys
import os
from py.xml import html

@pytest.mark.optionalhook
def pytest_html_results_table_header(cells):
	cells.insert(2, html.th('Waveform'))
	cells.pop()

@pytest.mark.optionalhook
def pytest_html_results_table_row(report, cells):
	waveform = html.td("N/A")
	if report.trace:
		waveform = html.td(html.a("waveform-trace", href=report.trace))

	cells.insert(2, waveform)
	cells.pop()

@pytest.mark.hookwrapper
def pytest_runtest_makereport(item, call):
	outcome = yield
	report = outcome.get_result()
	report.trace = None
	try:
		report.trace = item.funcargs["filename"]
		report.trace += '.vcd'
	except:
		pass

