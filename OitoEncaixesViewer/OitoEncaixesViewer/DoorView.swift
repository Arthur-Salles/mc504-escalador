//
//  DoorView.swift
//  SeisEncaixesViewer
//
//  Created by Ariadne Bigheti on 21/05/23.
//

import SwiftUI

struct DoorView: View {
    var gymCapacity: Int
    
    var body: some View {
        HStack {
            Rectangle()
                .frame(width: 120, height: 10)
                .foregroundColor(.clear)
            Rectangle()
                .frame(height: 15)
                .foregroundColor(.black)
        }
    }
}
