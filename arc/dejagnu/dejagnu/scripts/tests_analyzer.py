#!/usr/bin/env python3

import re
from typing import List, Dict

RE_COLLECTION = r'^Running.*/(?P<group>.*)/(?P<collection>.*\.exp) \.\.\.'
RE_TEST = r'^(?P<status>PASS|FAIL|XFAIL|UNTESTED|UNSUPPORTED|UNRESOLVED): .*\.exp: (?P<name>.*)'

def parse_summary(text: str) -> List[Dict]:
    '''
    {
        'name': 'literals.exp'
        'group': 'gdb.ada',
        'tests': [
            {
                'name': '...',
                'status': 'PASS' | 'FAIL' | 'XFAIL' | 'UNTESTED' | 'UNSUPPORTED' | 'UNRESOLVED'
            }
        ]
    }
    '''
    lines = text.splitlines()
    results = []
    current = None

    for line in lines:
        # Try to catch a new collection
        collection_match = re.search(RE_COLLECTION, line)
        if collection_match is not None:
            current = {
                'name': collection_match['collection'],
                'group': collection_match['group'],
                'tests': []
            }

            results.append(current)
            continue

        # Try to catch a test
        test_match = re.search(RE_TEST, line)
        if test_match is not None:
            if current is None:
                raise Exception('Test is found but collection is empty')
            test = {
                'name': test_match.group('name'),
                'status': test_match.group('status')
            }
            current['tests'].append(test)

    return results

def parsed_summary_to_plain(summary: List[Dict]) -> List[Dict]:
    plain_summary = []
    for collection in summary:
        for test in collection['tests']:
            plain_summary.append({
                'status': test['status'],
                'group': collection['group'],
                'collection': collection['name'],
                'instance': test['name']
            })
    return plain_summary

def main():
    path = 'examples/nsim/gdb.sum'
    with open(path, 'r', encoding='utf-8') as f:
        summary = parse_summary(f.read())
        nsim_plain_summary = parsed_summary_to_plain(summary)
        nsim_list = ['{}: {}/{}: {}'.format(test['status'], test['group'], test['collection'], test['instance']) for test in nsim_plain_summary]

    path = 'examples/hsdk/gdb.sum'
    with open(path, 'r', encoding='utf-8') as f:
        summary = parse_summary(f.read())
        hsdk_plain_summary = parsed_summary_to_plain(summary)
        hsdk_list = ['{}: {}/{}: {}'.format(test['status'], test['group'], test['collection'], test['instance']) for test in hsdk_plain_summary]
    
    nsim_list = list(filter(lambda x: re.search(r'^(FAIL|UNTESTED|UNRESOLVED)', x) is not None, nsim_list))
    hsdk_list = list(filter(lambda x: re.search(r'^(FAIL|UNTESTED|UNRESOLVED)', x) is not None, hsdk_list))
    intersection = set(nsim_list) & set(hsdk_list)

    print('Intersection of important instances: {}'.format(len(intersection)))

    failing_tests = sorted(list(filter(lambda x: x.startswith('FAIL') and 'gdb.mi' not in x, intersection)))
    print('Fails: {}'.format(len(failing_tests)))

    failing_collections = []
    for failing_test in failing_tests:
        collection = failing_test.split(': ')[1]
        if collection not in failing_collections:
            failing_collections.append(collection)
            print(collection)
            print()



if __name__ == '__main__':
    main()
